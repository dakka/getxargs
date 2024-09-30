/*

                                  boolEAN.CPP

        Methods for the boolean class
        for the command line argument parser
            by David Dight

        Last updated: Monday, 28/12/1992, 5:32:14 pm

*/

//static const char *rcsid = "$Id: boolean.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
Boolean::Boolean (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 bool *valloc, bool initval) : Argument (sw, sw_n, sw_x, desc, NOPARAM),
    argloc(valloc)
{
	*argloc = initval;
}

/*----------------------------------------------------------------------------
**  This overloaded method is called for Arguments with no dependants.
**  The value at argloc is inverted.
**---------------------------------------------------------------------------*/
void Boolean::parse ()
{
    *argloc = (*argloc) ? false : true;
    parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void Boolean::mk_default (ostream& ostr)
{
    if (*argloc)
        ostr << "True";
    else
        ostr << "False";
}

/* EOM: boolEAN.CPP ----------------------------------------------------------*/
