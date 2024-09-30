/*

                                   DOUBLE.CPP

        Methods for the double class
        for the command line argument parser
            by David Dight

        Last updated: Saturday,  2/01/1993, 1:21:35 pm

*/

//static char const *rcsid = "$Id: double.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
Double::Double (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
	double *valloc, double initval) : Argument (sw, sw_n, sw_x, desc, NEEDSPARAM), argloc(valloc)
{
    *argloc = initval;
}

/*----------------------------------------------------------------------------
**  This method takes a char* to the command line value (not including
**  the switch) and attempts to parse a double out of it, placing the
**  value at argloc.
**---------------------------------------------------------------------------*/
void Double::parse (char *str)
{
	istringstream istr (str);

	 istr.setf(ios::fixed);
	 istr.width(4);

    if (istr >> *argloc)
        parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void Double::mk_default (ostream& ostr)
{
    ostr << *argloc;
}

/* EOM: DOUBLE.CPP ----------------------------------------------------------*/
