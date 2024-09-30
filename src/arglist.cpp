/*

							   ARGLIST.CPP

	 defines the class arglist
	 for the command line argument parser
		 by David Dight

	 Last updated: Monday,  4/01/1993, 12:08:22 am

*/

//static const char *rcsid = "$Id: arglist.cpp 501 2010-01-22 01:30:08Z davidd $";

#include "argument.h"

/*----------------------------------------------------------------------------
Contructor
**---------------------------------------------------------------------------*/
Arglist::Arglist (int margs, int msws, int flg, const char swt, const char *unstr)
	: swnum(), argflags(flg), argcnt(), unswitched(), getunswitched(), argoverflow(), switcherrors(),
	sw_type(swt), unswbuffer(new (char *[maxsws = msws])), unswstring(const_cast<char*>(unstr)), progname(),
	list(new (Argument *[maxargs = margs]))
{
}

/*----------------------------------------------------------------------------
Destructor
**---------------------------------------------------------------------------*/
Arglist::~Arglist ()
{
	for (Argument **p(list); p < list + swnum; delete *p++)
	 ;
	delete[] list;

	for (char **s(unswbuffer); s < unswbuffer + unswitched; delete[] *s++)
	 ;
	delete[] unswbuffer;
	delete[] progname;
}

/*----------------------------------------------------------------------------
Add an Argument to Arglist
**---------------------------------------------------------------------------*/
int Arglist::operator += (Argument *p)
{
	if (swnum + 1 <= maxsws)
	{
		for (Argument **t(list); swnum && t < list + swnum; t++)
		{
			if (**t == *p)
			{
				cerr << "Switch tag: " << sw_type;
				p->sw->mk_alias(cerr) << " already defined in: " << sw_type;
				(*t)->sw->mk_alias(cerr) << endl;
				delete p;
				return -1;
			}
		}

	 list[swnum++] = p;
	 return 0;
	}
	delete p;
	return -1;
}

/*----------------------------------------------------------------------------
Argument parser, taking input from an istream
**---------------------------------------------------------------------------*/
int Arglist::operator () (istream& istr)
{
	char **argv(new (char *[maxsws]));
	char buff[MAXSTRLEN]{};
	int argc(0);

	while (!istr.fail() && istr >> buff && argc <= maxsws)
	{
	 char *p(new char[strlen(buff)+1]);
	 strcpy (p, buff);
	 argv[argc++] = p;
	}
	return (*this)(argc, argv);		 // call main processor
}

/*----------------------------------------------------------------------------
Argument parser, taking input from C main style argc/argv pair
**---------------------------------------------------------------------------*/
int Arglist::operator () (int argc, char **argv)
{
	Argument *p;

	if (argc >= 1)
	{
		char *pt;
		for (pt = *argv + strlen(*argv) - 1; pt > *argv; pt--)
		{
			if (*pt == '\\' || *pt == '/')	// remove path if present
			{							   // (for DOS users)
				pt++;
				break;
			}
			else if (*pt == '.')
				*pt = 0;
		}
		progname = new char[strlen(pt)+1];	   // program name
		strcpy (progname, pt);
	}
	else
		return 0;								   // no args

	if (argc > maxsws + 1)						 // process maxsws argc's
	{											   // only; ignore any more
		argoverflow = argc - maxsws + 1;		   // argoverflow set
		argc = maxsws + 1;
	}

	while (--argc)							  // while cmd line args
	{										   // test for a switch
		if (**++argv == sw_type && *(*argv + 1) != sw_type)
		{
			while (*++*argv)					// allow switch stacking
			{
				if ((p = findtag (*argv)))		// global switch search
				{
					argcnt++;

					if (p->isparsed() && !isflag(OVERWRITE))
						cerr << sw_type << p->sw->getfoundalias() << ':'
						<< "already passed (" << p->isparsed() + 1
						<< ") ignoring previous value" << endl;

					if (p->isdependant())
					{						   // take next arg as value

	// try to compress a bit of logic

						bool nothingat0 (!(*(*argv + p->sw->aliaslen))),
							nothingat1 (!(*(*argv + p->sw->aliaslen + 1))),
							iscommaat0 (*(*argv + p->sw->aliaslen) == ','),
							iscommaat1 (*(*argv + p->sw->aliaslen + 1) == ',');

						bool goodcomma (iscommaat0 && !nothingat1);
						bool ignorecomma (goodcomma && iscommaat1);

						if ((nothingat0 || iscommaat0) && !ignorecomma)
						{
							if ((nothingat0 || !goodcomma) && argc - 1 > 0 && (**(argv+1) != sw_type))
							{
								--argc;
								p->parse (*++argv);
							}
							else				// no more args
							{				   // take from cin
								char s[MAXSTRLEN];

								if (!isflag(NOPROMPT))
									cerr << sw_type << p->sw->getfoundalias() << '<' << p->getdesc() << ">:";
								 //if (cin >> s)
								if (cin.getline (s, MAXSTRLEN - 1))
									p->parse (s);
								else
									cerr << sw_type << p->sw->getfoundalias() << " ignored." << endl;

								if (goodcomma)
								{			  // backup handled by dropping ','
									*argv += p->sw->aliaslen;
									continue;
								}
							}
						}
						else						// value appends switch
						{
							if (ignorecomma)
								++*argv;
							p->parse (*argv + p->sw->aliaslen);
						}
						break;			  // no stacking on end for these
					}
					else					// no value expected
					{
						*argv += p->sw->aliaslen - 1;  // back up for *++*argv
						p->parse ();
					}
				}
				else
				{
					cerr << progname << ": unknown switch: " << sw_type << **argv << endl;
					switcherrors++;
				}
			}						   // loop, search for stacked params
		}
		else							// not a switched parameter
		{
			if (*(*argv + 1) == sw_type)	// allow sw_type char
				*argv += 1;				 // to be passed as an unswitched
			if (isflag(KEEPUNSWITCHED))	 // keep ?
				add_unsw (*argv);
			else
				cerr << progname << ": unknown parameter: " << *argv << endl;
			unswitched++;
		}
	}

	read_unsws (cin);		   // need more unswitched values? take from cin

	checkswitches();
	if (isflag (USAGEONERROR) && switcherrors)
	{
		mk_usageshort(cerr);
		return -1;
	}

	return argcnt;
}

/*----------------------------------------------------------------------------
Check Arglist for switch conflicts
**---------------------------------------------------------------------------*/
int Arglist::checkswitches ()
{
	for (Argument **p(list); p < list + swnum; p++)
	{
		for ( Argument **t(list); t < list + swnum; t++)
		{
			if (t == p)
				continue;		   // don't test self

			if (**t < **p)		  // needed switches
			{
				cerr << sw_type;
				(*t)->sw->mk_alias(cerr) << " needs " << sw_type;
				(*p)->sw->mk_alias(cerr) << endl;
				switcherrors++;
			}
			if (**t > **p)		  // excluded switches
			{
				cerr << sw_type;
				(*t)->sw->mk_alias(cerr) << " excludes " << sw_type;
				(*p)->sw->mk_alias(cerr) << endl;
				switcherrors++;
			}
		}
	}

	return switcherrors;
}

/*----------------------------------------------------------------------------
Returns Argument that matches a command line switch
**---------------------------------------------------------------------------*/
Argument *Arglist::findtag (const char *find)  // find widest matching tag
{
	int maxwidthtag(-1), maxswitch, maxwidth(0), k;

	for (int i(0); i < swnum; i++)
	{
		for (int j(0); j < (list[i])->sw->gettagnum(); j++)
		{
			if (memcmp ((list[i])->sw->get(j), find, (k = strlen((list[i])->sw->get(j)))) == 0)
				if (maxwidth < k)
					maxwidthtag = j, maxwidth = k, maxswitch = i;
		}
	}

	if (maxwidthtag >= 0)
	{
		(list[maxswitch])->sw->set (maxwidthtag, maxwidth);
		return list[maxswitch];
	}
	return 0;
}

/* EOM: arglist.cpp  --------------------------------------------------------*/
