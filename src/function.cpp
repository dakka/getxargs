/*

                                  FUNCTION.CPP

        Methods for the function class
        for the command line argument parser
            by David Dight

        Last updated: Saturday,  2/01/1993, 1:21:37 pm

*/

//static const char *rcsid = "$Id: function.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
Constructor
**---------------------------------------------------------------------------*/
Function::Function (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 int (*initval) ()) : Argument (sw, sw_n, sw_x, desc, NOPARAM),
    argloc(initval), retval()
{
}

Function::Function (const char *sw, const char *sw_n, const char *sw_x, const char *desc,
 int (*initval) (const char *)) : Argument (sw, sw_n, sw_x, desc, NEEDSPARAM),
    argloc((int (*) ()) initval), retval()
{
}

/*----------------------------------------------------------------------------
**  This overloaded method is called for Arguments with no dependants.
**  The function at argloc is called.
**---------------------------------------------------------------------------*/
void Function::parse ()
{
    retval = (*argloc) ();
    parsed++;
}

/*----------------------------------------------------------------------------
**  This overloaded method calls a function with a char * args
**  The function at argloc is called.
**---------------------------------------------------------------------------*/
void Function::parse (char *str)
{
    retval = ((int (*) (char *)) *argloc) (str);
    parsed++;
}

/*----------------------------------------------------------------------------
**  This method prints the default value at argloc.
**---------------------------------------------------------------------------*/
void Function::mk_default (ostream& ostr)
{
    if (parsed)
        ostr << "function returned (" << retval << ')';
    else
        ostr << "function at " << (void *) *argloc;
}

/* EOM: FUNCTION.CPP --------------------------------------------------------*/
