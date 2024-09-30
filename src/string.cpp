/*

                                   STRING.CPP

        Methods for the string class
        for the command line argument parser
            by David Dight

        Last updated: Monday, 28/12/1992, 5:32:11 pm

*/

//static const char *rcsid = "$Id: string.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
String::String (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 char **valloc, const char *initval) : Argument (sw, sw_n, sw_x, desc, NEEDSPARAM),
    argloc(valloc)
{
    *argloc = new char[strlen(initval)+1];
    strcpy (*argloc, initval);
}

/*----------------------------------------------------------------------------
**  This is the default destructor for a String, and simply frees any storage.
**---------------------------------------------------------------------------*/
String::~String ()
{
    delete[] *argloc;
}

/*----------------------------------------------------------------------------
**  This method takes a char* to the command line value (not including
**  the switch) and attempts to copy a string out of it, placing the
**  value at argloc. Escape sequences are translated.
**---------------------------------------------------------------------------*/
void String::parse (char *str)
{
    char *buff(new char[MAXSTRLEN]), *s(buff), c;

    for (char *d(str); *d && s < buff + MAXSTRLEN; d++, s++)
    {
        if (*d == '\\' && (c = getescape (*(d + 1))))
        {
            *s = c;
            d++;                            // account for 2 chars
        }
        else
            *s = *d;
    }
    *s = 0;

    delete[] *argloc;
    *argloc = new char[strlen(buff)+1];
    strcpy (*argloc, buff);
    delete[] buff;
    parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void String::mk_default (ostream& ostr)
{
    if (**argloc)
        ostr << *argloc;
    else
        ostr << "(null string)";
}

/* EOM: STRING.CPP ----------------------------------------------------------*/
