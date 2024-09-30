/*

                                  ARGUMENT.CPP

        Methods for the argument class
        for the command line argument parser
            by David Dight

        Last updated: Saturday,  2/01/1993, 1:21:33 pm

*/

//static const char *rcsid = "$Id: argument.cpp 501 2010-01-22 01:30:08Z davidd $";
#include "argument.h"

/*----------------------------------------------------------------------------
**  This constructor takes 5 arguments, x_sw:a string of valid switch
**  tags for this arguemnt (e.g."dD"),x_sw_needed:a string of needed
**  switch tags that must be passed with this switch,x_sw_excluded:a
**  string of excluded switch tags that cannot be passed with this
**  switch,x_description:a string describing this switch,dep:this
**  determines whether this switch needs a value or not, e.g. a
**  Boolean has no value (this is handled in the class definition).
**---------------------------------------------------------------------------*/
Argument::Argument (const char *x_sw, const char *x_sw_needed, const char *x_sw_excluded,
  const char *x_description, DEPENDANT dep)
	: description(x_description), dependant((dep == NEEDSPARAM) ? true : false), parsed(),
	sw(new Tags (x_sw)), sw_needed(new Tags (x_sw_needed)),
	sw_excluded(new Tags (x_sw_excluded))
{
}

/*----------------------------------------------------------------------------
Destructor
**---------------------------------------------------------------------------*/
Argument::~Argument ()
{
    delete sw;
    delete sw_needed;
    delete sw_excluded;
}

/*----------------------------------------------------------------------------
**  This method creates a help message about (this) Argument, in the
**  form: <sw_type><switch aliases><description>,<default>, e.g.
**  -b boolean arg, default False
**---------------------------------------------------------------------------*/
ostream& Argument::help (const char sw_t, ostream& ostr)
{
    ostr << sw_t;
    sw->mk_alias (ostr);
    if (dependant)
        ostr << " <" << description << '>';
    else
        ostr << ' ' << description;
	 if (!parsed )
	 {
		 ostr << ", default ";
		 mk_default (ostr);
	 }
    return ostr;
}

/*----------------------------------------------------------------------------
**  This method tests the two args to see if they contain the same
**  switch tags (==).
**---------------------------------------------------------------------------*/
int operator == (const Argument& a, const Argument& b)
{
    for (int i(0); i < a.sw->gettagnum(); i++)
        for (int j(0); j < b.sw->gettagnum(); j++)
            if (strcmp(a.sw->get(i), b.sw->get(j)) == 0
             && strlen(a.sw->get(i)) == strlen(b.sw->get(j)) )
                return 1;
    return 0;
}

/*----------------------------------------------------------------------------
**  This method returns true if arg b was needed by arg a and not parsed.
**---------------------------------------------------------------------------*/
int operator < (const Argument& a, const Argument& b)
{
    if (a.isparsed() && !b.isparsed())
	 {
        for (int i(0); i < a.sw_needed->gettagnum(); i++)
            if (*a.sw_needed->get1st() == '*')
                return 1;
            else for (int j(0); j < b.sw->gettagnum(); j++)
                  if (strcmp (a.sw_needed->get(i), b.sw->get(j) ) == 0
                  && strlen (a.sw_needed->get(i)) == strlen(b.sw->get(j)))
                    return 1;
	 }
    return 0;
}

/*----------------------------------------------------------------------------
**  This method returns true if arg b was excluded by arg a and was parsed.
**---------------------------------------------------------------------------*/
int operator > (const Argument& a, const Argument& b)
{
    if (a.isparsed() && b.isparsed())
	 {
        for (int i(0); i < a.sw_excluded->gettagnum(); i++)
            if ( *a.sw_excluded->get1st() == '*')
                return 1;
            else for (int j(0); j < b.sw->gettagnum(); j++)
                if (strcmp (a.sw_excluded->get(i), b.sw->get(j) ) == 0
                  && strlen (a.sw_excluded->get(i)) == strlen(b.sw->get(j)))
                    return 1;
	 }
    return 0;
}

/*----------------------------------------------------------------------------
**  Used by string and character arguments.
**---------------------------------------------------------------------------*/
char getescape (char escseq)
{
    switch (escseq)
    {
        case 's': return ' ';
        case 'n': return '\n';
        case 'b': return '\b';
        case 't': return '\t';
        case 'a': return '\a';
        case 'r': return '\r';
        case 'f': return '\f';
        default : break;
    }
    return 0;
}

/* EOM: argument.cpp  -------------------------------------------------------*/
