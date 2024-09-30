/*

                                   ARGUMENT.H


        definitions for argument.cpp
        command line argument parser
            by David Dight

        Last updated: Saturday, 24/04/1993, 10:52:21 pm

*/

// $Id: argument.h 501 2010-01-22 01:30:08Z davidd $
//
#if !defined ( _ARGUMENT_H_ )

#define     _ARGUMENT_H_

#define     MAXARGS             64
#define     MAXTAGS             8
#define     MAXTAGLEN           16
#define     MAXSWS              32
#define     MAXALIASES          32

#define     USAGEONERROR        0x1
#define     KEEPUNSWITCHED      0x2
#define     NOPROMPT            0x4
#define     OVERWRITE           0x8


enum DEPENDANT          { NOPARAM = 0, NEEDSPARAM };

/*----------------------------------------------------------------------------*/
#include <iostream>
using namespace std;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
//#include <strstream>
/*----------------------------------------------------------------------------*/
char getescape (char);
/*----------------------------------------------------------------------------*/

class Tags
{
    char **taglist;
    int tagnum;
    int foundalias;

public:

    int aliaslen;

    Tags (const char *);
    virtual ~Tags ();
    int add (const char *);
    char *get (int);
    char *get1st () { return get(0); };
    char *getfoundalias ();
    ostream& mk_alias (ostream& );
    ostream& mk_list (ostream& );
    int gettagnum () const { return tagnum; }
    void set (int tag, int len) { foundalias = tag; aliaslen = len; }
};


/*----------------------------------------------------------------------------
**  This is the Argument base class. This class contains common datum
**  and methods for all argument objects.
**---------------------------------------------------------------------------*/
class Argument
{
    const char        *description;       // help string
    bool        dependant;          // needs further data after switch

protected:

    int         parsed;             // was successfully parsed

public:

    Tags        *sw;                // switch tags
    Tags        *sw_needed;         // needs these switches
    Tags        *sw_excluded;       // but not these

    Argument (const char *, const char *, const char *, const char *, DEPENDANT);
    virtual ~Argument ();
    virtual void parse (char *) {}
    virtual void parse () {}
    virtual void mk_default (ostream& ) = 0;
    virtual void *getloc () = 0;
    ostream& help (const char, ostream& );
    int isparsed () const { return parsed;}
    bool isdependant () const { return dependant; }
    const char *getdesc() const { return description; }

    friend int operator == (const Argument& , const Argument& );
    friend int operator < (const Argument& , const Argument& );
    friend int operator > (const Argument& , const Argument& );
};

/*----------------------------------------------------------------------------
**  This object handles a boolean argument type
**---------------------------------------------------------------------------*/
class Boolean : public Argument
{
    bool  *argloc;

public:

    Boolean (const char *, const char *, const char *, const char *, bool *, bool);
    virtual ~Boolean () {}
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse ();
};

/*----------------------------------------------------------------------------
**  This object handles a single character argument type
**---------------------------------------------------------------------------*/
class Character : public Argument
{
    char *argloc;

public:

    Character (const char *, const char *, const char *, const char *, char *, const char);
    virtual ~Character () {}
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse (char *);
};

/*----------------------------------------------------------------------------
**  This object handles a double precision argument
**---------------------------------------------------------------------------*/
class Double : public Argument
{
    double  *argloc;

public:

    Double (const char *, const char *, const char *, const char *, double *, double);
    virtual ~Double () {}
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse (char *);
};

/*----------------------------------------------------------------------------
**  This object handles a function call argument (essentially bool -
**  if true, the function is called). The actual function called is stored at
**  the address pointed at by argloc. Function return value is kept in retval.
**---------------------------------------------------------------------------*/
class Function : public Argument
{
    int (*argloc) ();
    int retval;

public:

    Function (const char *, const char *, const char *, const char *, int (*) ());
    Function (const char *, const char *, const char *, const char *, int (*) (const char *));
    virtual ~Function () {}
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse (char *);
    void parse ();
};

/*----------------------------------------------------------------------------
**  This object stores an integer argument.
**---------------------------------------------------------------------------*/
class Integer : public Argument
{
    int   *argloc;

public:

    Integer (const char *, const char *, const char *, const char *, int *, int);
    virtual ~Integer () {}
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse (char *);
};

/*----------------------------------------------------------------------------
**  This object stores allocates storage and copies a string argument.
**  The actual string is stored at the pointer pointed at by argloc.
**---------------------------------------------------------------------------*/
class String : public Argument
{
    char   **argloc;

public:

    String (const char *, const char *, const char *, const char *, char **, const char *);
    virtual ~String ();
    void mk_default (ostream& );
    void *getloc () { return (void *) argloc; }
    void parse (char *);
};

#include "arglist.h"

#endif //  _ARGUMENT_H_

/* EOM: argument.h ----------------------------------------------------------*/
