/*

                                  INTEGER.CPP

        Methods for the class integer
        for the command line argument parser
            by David Dight

        Last updated: Monday, 28/12/1992, 5:32:12 pm

*/

//static const char *rcsid = "$Id: integer.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
Integer::Integer (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 int *valloc, int initval) : Argument (sw, sw_n, sw_x, desc, NEEDSPARAM),
    argloc(valloc)
{
    *argloc = initval;
}

/*----------------------------------------------------------------------------
**  This method takes a char* to the command line value (not including
**  the switch) and attempts to parse an int out of it, placing the
**  value at argloc.
**---------------------------------------------------------------------------*/
void Integer::parse (char *str)
{
    istringstream istr (str);

    //if (istr >> dec >> *argloc)
    if (istr >> *argloc)
        parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void Integer::mk_default (ostream& ostr)
{
    ostr << *argloc;
}

/* EOM: INTEGER.CPP  --------------------------------------------------------*/
