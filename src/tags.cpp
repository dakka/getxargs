/*

                                    TAGS.CPP

        defines the Tags object
        for the command line argument parser
            by David Dight

        Last update:Friday,  1/01/1993, 2:44:10 am

*/

//static const char *rcsid = "$Id: tags.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Contructor
**---------------------------------------------------------------------------*/
Tags::Tags (const char *s)
{
    tagnum = foundalias = aliaslen = 0;

    if (!*s)
        taglist = new (char *[MAXTAGS]);
	else
	{
		char *t, *p(new char [MAXTAGLEN + 1]);
		taglist = new (char *[MAXTAGS]);

		*p = 0;
		t = p;
		do
		{
			if (*s == ',' || *s == '|')
			{
				*t = 0;
				if (add (p))
					break;
				t = p;
			}
			else if (! *(s + 1) || t + 1 > p + MAXTAGLEN)
			{
				*t++ = *s;
				*t = 0;
				add (p);
			}
			else
				*t++ = *s;
		}
		while (*++s);
		delete[] p;
	}
}

/*----------------------------------------------------------------------------
Destructor
**---------------------------------------------------------------------------*/
Tags::~Tags ()
{
    for (char **p(taglist); p < taglist + tagnum; delete[] *p++)
        ;
    delete[] taglist;
}

/*----------------------------------------------------------------------------
This method adds a string to the taglist
**---------------------------------------------------------------------------*/
int Tags::add (const char *s)
{
    if (tagnum + 1 > MAXTAGS)
        return -1;
    taglist[tagnum] = new char[strlen(s)+1];
    strcpy (taglist[tagnum++], s);
    return 0;
}

/*----------------------------------------------------------------------------
This method returns the i'th tag
**---------------------------------------------------------------------------*/
char *Tags::get (int i)
{
    if (0 <= i && i < tagnum)
        return taglist[i];
    return 0;
}

/*----------------------------------------------------------------------------
This method creates a list of aliases for a Tag in an ostream
**---------------------------------------------------------------------------*/
ostream& Tags::mk_alias (ostream& ostr)
{
    for (int i(0); i < tagnum; i++)
    {
        ostr << taglist[i];

        if (i + 1 < tagnum && tagnum > 1)
        {
            if (i == 0)
                ostr << '(';
            else
                ostr << ',';
         }
    }
    if (tagnum > 1)
        ostr << ')';
    return ostr;
}

/*----------------------------------------------------------------------------
This method creates a list of aliases for a Tag (others)
**---------------------------------------------------------------------------*/
ostream& Tags::mk_list (ostream& ostr)
{
    for (int i(0); i < tagnum; i++)
    {
        ostr << taglist[i];

        if (i + 1 < tagnum && tagnum > 1)
            ostr << ',';
    }
    return ostr;
}

/*----------------------------------------------------------------------------
This method returns either the passed tag or the 1st tag if not passed
**---------------------------------------------------------------------------*/
char *Tags::getfoundalias ()
{
    if (aliaslen)
        return get(foundalias);
    return get1st();
}

/* EOM: tags.cpp  ------------------------------------------------------------*/
