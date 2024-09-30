/*

                                  ARGPROC.CPP

        methods for arglist
        for the command line argument parser
            by David Dight

        Last updated: Saturday,  2/01/1993, 9:28:12 pm

*/
//static const char *rcsid = "$Id: argproc.cpp 50 2006-10-23 04:00:19Z davidd $";

#include "argument.h"
#include <iomanip>

/*----------------------------------------------------------------------------
Output a string containing all switches to an ostream
**---------------------------------------------------------------------------*/
ostream& Arglist::getwildcards (const Argument *s, ostream& ostr)
{
    for (Argument **p(list); p < list + swnum; p++)
    {
        if (s == *p)            // don't test telf
            continue;
        ostr << (*p)->sw->getfoundalias();
        if (p + 1 < list + swnum)
            ostr << ',';
    }
    return ostr;
}

/*----------------------------------------------------------------------------
Tests a pointer to a switch associated value, returns true if it was passed
**---------------------------------------------------------------------------*/
int Arglist::wasparsed (const void *ptr)
{
    for (Argument **p = list; p < list + swnum; p++)
        if ((*p)->isparsed() && (*p)->getloc() == ptr)
            return 1;
    return 0;
}

/*----------------------------------------------------------------------------
Return i'th unswitched string (0=1st)
**---------------------------------------------------------------------------*/
char *Arglist::get_unsw (int idx)
{
    return (idx < 0 || idx >= unswitched) ? (char*)"" : unswbuffer[idx];
}

/*----------------------------------------------------------------------------
Add a string to the unswitched list
**---------------------------------------------------------------------------*/
void Arglist::add_unsw (char *str)
{
    unswbuffer[unswitched] = new char[strlen(str)+1];
    strcpy (unswbuffer[unswitched], str);
}

/*----------------------------------------------------------------------------
Output all unswitched values to an ostream
**---------------------------------------------------------------------------*/
ostream& Arglist::pr_unsws (ostream& ostr)
{
    if (isflag(KEEPUNSWITCHED))
        for (int i(0); i < unswitched; i++)
            ostr << get_unsw (i) << endl;
    return ostr;
}

/*----------------------------------------------------------------------------
Print every switch with default value
**---------------------------------------------------------------------------*/
ostream& Arglist::pr_values (ostream& xostr)
{

    for (Argument **p(list); p < list + swnum; p++)
	 {
        if ((*p)->isparsed())
        {
				ostringstream ostr;
            ostr << sw_type << (*p)->sw->getfoundalias() << ':';
            (*p)->mk_default(ostr);
            ostr << endl;
            xostr << ostr.str();
            //ostr.seekp(0);
        }
	 }
    return xostr;
}

/*----------------------------------------------------------------------------
Output a short help msg to an ostream
**---------------------------------------------------------------------------*/
ostream& Arglist::mk_usageshort (ostream& ostr)
{
    if (version)
        ostr << '(' << version << ") ";
    ostr << "usage: " << progname;
    if (swnum)
        ostr << " [" << sw_type;
    for (Argument **p(list); p < list + swnum; p++)
        ostr << (*p)->sw->getfoundalias();
    if (swnum)
        ostr << ']';
    if (*unswstring)
        ostr << ' ' << unswstring;
    ostr << endl;
    return ostr;
}

/*----------------------------------------------------------------------------
Output a long help msg to an ostream
**---------------------------------------------------------------------------*/
ostream& Arglist::mk_usagelong (ostream& xostr)
{
    mk_usageshort (xostr);

    for (Argument **p(list); p < list + swnum; p++)
    {
		 ostringstream ostr;
        //ostr.seekp(0);
			ostr << '\t';
        (*p)->help(sw_type, ostr);

        if ((*p)->sw_needed->gettagnum())
        {
            ostr << ", needs " << sw_type;
            if (*(*p)->sw_needed->get1st() == '*')
                getwildcards (*p, ostr);
            else
                (*p)->sw_needed->mk_list(ostr);
        }
        if ((*p)->sw_excluded->gettagnum())
        {
            ostr << ", excluded " << sw_type;
            if (*(*p)->sw_excluded->get1st() == '*')
                getwildcards (*p, ostr);
            else
                (*p)->sw_excluded->mk_list(ostr);
        }
        ostr << endl;
        xostr << ostr.str();
    }
    return xostr;
}

/*----------------------------------------------------------------------------
Read more unswitched values from an istream
**---------------------------------------------------------------------------*/
int Arglist::read_unsws (istream& istr)
{
    if (isflag(KEEPUNSWITCHED))
        while (unswitched < getunswitched)
        {
            char s[MAXSTRLEN];

            if (!isflag(NOPROMPT))
                cerr << unswitched + 1 << ':';
            istr >> s;
            add_unsw (s);
            unswitched++;
        }
    return unswitched;
}

