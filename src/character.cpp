/*

                                  CHARACTER.CPP

        Methods for the character class
        for the command line argument parser
            by David Dight

        Last updated: Saturday,  2/01/1993, 1:20:53 pm

*/

//static const char *rcsid = "$Id: character.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
Character::Character (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 char *valloc, const char initval) : Argument (sw, sw_n, sw_x, desc, NEEDSPARAM),
    argloc(valloc)
{
    *argloc = initval;
}

/*----------------------------------------------------------------------------
**  This method takes a char* to the command line value (not including
**  the switch) and attempts to parse a char out of it, placing the
**  value at argloc.
**---------------------------------------------------------------------------*/
void Character::parse (char *str)
{
    char c;

    if (*str == '\\' && (c = getescape (*(str + 1))))
        *argloc = c;
    else if (! (*argloc = *str))
        return;
    parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void Character::mk_default (ostream& ostr)
{
    if (*argloc)
        ostr << *argloc;
    else
        ostr << "\'\\0\'";
    ostr << " (" << (int) *argloc << ')';
}

/* EOM: CHARACTER.CPP --------------------------------------------------------*/
