/*

								   ARGLIST.H


		definitions for arglist.cpp
		command line argument parser
			by David Dight

		Last updated: Saturday, 24/04/1993, 10:52:45 pm

*/

// $Id: arglist.h 501 2010-01-22 01:30:08Z davidd $
//
#if !defined ( _ARGLIST_H_ )

#define	 _ARGLIST_H_

#define	 MAXSTRLEN			   128

/*----------------------------------------------------------------------------
**  This object handles the processing of the arguments. Calls are
**  made to initialize the handler, set up switch argument types,
**  and handle the parsing, switch checking and help string services.
**---------------------------------------------------------------------------*/
class Arglist
{
	int maxargs;				// allowed to program
	int maxsws;				 // defined switches

	int swnum;				  // actual number of switches declared
	int argflags;			   // global argument flags
	int argcnt;				 // the number of arguments processed ok

	int unswitched;			 // set to the number of unswitched strings
	int getunswitched;		  // set to the number of unswitched stringstoget
	int argoverflow;			// the number of overflowed arguments passed
	int switcherrors;		   // set to the number of errors

	char *version;			  // optional program version
	char sw_type;			   // e.g. '-' for UNIX, or '/' for DOS
	char **unswbuffer;		  // place to put unswitched strings
	char *unswstring;		   // tag for unswitched strings
	char *progname;			 // copy of argv[0][]
	Argument **list;			// place to store switch argument

	int checkswitches ();
	Argument *findtag (const char *);
	ostream& getwildcards (const Argument *, ostream& );
	void add_unsw (char *);

public:

	Arglist (int=MAXARGS, int=MAXSWS, int=0, const char='-', const char * = "");
	virtual ~Arglist ();
	int read_unsws (istream& );
	int wasparsed (const void *);
	int isflag (const int flag) const { return (argflags & flag); }
	int numparsed () const { return argcnt; }
	int numunswitched () const { return unswitched; }
	int numerrors () const { return switcherrors; }
	int isoverflow () const { return argoverflow; }
	char *get_unsw (int);

	void setversion (const char *v) { version = const_cast<char *>(v); }
	void setunswitched (int num) { getunswitched = num; }
	int operator () (int, char **);
	int operator () (istream& );
	int operator += (Argument *);

	ostream& pr_unsws (ostream& );
	ostream& pr_values (ostream& );
	ostream& mk_usageshort (ostream& );
	ostream& mk_usagelong (ostream& );

	Arglist& operator << (int flg) { argflags |= flg; return *this; }
	Arglist& operator << (char swt) { sw_type = swt; return *this; }
	Arglist& operator << (char *unsw) { unswstring = unsw; return *this; }

	int add (const char *a, const char *b, const char *c, const char *d, bool *e, bool f)
		{ return *this += new Boolean (a, b, c, d, e, f);}
	int add (const char *a, const char *b, const char *c, const char *d, bool *e)
		{  return *this += new Boolean (a, b, c, d, e, false); }
	int add (const char *a, const char *b, bool *c, bool d)
		{ return *this += new Boolean (a, "", "", b, c, d); }
	int add (const char *a, const char *b, bool *c)
		{ return *this += new Boolean (a, "", "", b, c, false); }

	int add (const char *a, const char *b, const char *c, const char *d, char *e, const char f)
		{ return *this += new Character (a, b, c, d, e, f); }
	int add (const char *a, const char *b, const char *c, const char *d, char *e)
		{ return *this += new Character (a, b, c, d, e, '\0'); }
	int add (const char *a, const char *b, char *c, const char d)
		{ return *this += new Character (a, "", "", b, c, d); }
	int add (const char *a, const char *b, char *c)
		{ return *this += new Character (a, "", "", b, c, '\0'); }

	int add (const char *a, const char *b, const char *c, const char *d, double *e, double f)
		{ return *this += new Double (a, b, c, d, e, f); }
	int add (const char *a, const char *b, const char *c, const char *d, double *e)
		{ return *this += new Double (a, b, c, d, e, 0.0); }
	int add (const char *a, const char *b, double *c, double d)
		{ return *this += new Double (a, "", "", b, c, d); }
	int add (const char *a, const char *b, double *c)
		{ return *this += new Double (a, "", "", b, c, 0.0); }

	int add (const char *a, const char *b, const char *c, const char *d, int (*e) () )
		{ return *this += new Function (a, b, c, d, e); }
	int add (const char *a, const char *b, int (*c) ())
		{ return *this += new Function (a, "", "", b, c); }
	int add (const char *a, const char *b, const char *c, const char *d, int (*e) (const char *))
		{ return *this += new Function (a, b, c, d, e); }
	int add (const char *a, const char *b, int (*c) (const char *))
		{ return *this += new Function (a, "", "", b, c); }

	int add (const char *a, const char *b, const char *c, const char *d, int *e, int f)
		{ return *this += new Integer (a, b, c, d, e, f); }
	int add (const char *a, const char *b, const char *c, const char *d, int *e)
		{ return *this += new Integer (a, b, c, d, e, 0); }
	int add (const char *a, const char *b, int *c, int d)
		{ return *this += new Integer (a, "", "", b, c, d); }
	int add (const char *a, const char *b, int *c)
		{ return *this += new Integer (a, "", "", b, c, 0); }

	int add (const char *a, const char *b, const char *c, const char *d, char **e, const char *f)
		{ return *this += new String (a, b, c, d, e, f); }
	int add (const char *a, const char *b, const char *c, const char *d, char **e)
		{ return *this += new String (a, b, c, d, e, ""); }
	int add (const char *a, const char *b, char **c, const char *d)
		{ return *this += new String (a, "", "", b, c, d); }
	int add (const char *a, const char *b, char **c)
		{ return *this += new String (a, "", "", b, c, ""); }
};

// Inline method definitions


#endif //  _ARGLIST_H_

/* EOM: argument.h ----------------------------------------------------------*/
