#include "argument.h"

void print_results (Arglist& , int);
int funcA(const char *), funcB(const char *), funcC(const char *);

int main (int argc, char **argv)
{
    bool help;

    Arglist argl (32, 32, KEEPUNSWITCHED, '@', "parent unswitched values");
	 argl.setversion("1.01");

    argl.mk_usagelong (cerr);
    if (argl.add ("h,H,help,HELP", "", "?", "help arg", &help)
     || argl.add ("A,AARGLIST", "argument file", funcA)
     || argl.add ("B,BARGLIST", "argument file", funcB)
     || argl.add ("C,CARGLIST", "argument file", funcC)
     || argl (argc, argv) < 0
     || help
     || argl.numerrors() )
    {
        argl.mk_usagelong (cerr);
        return 1;
    }

    print_results (argl, argc);

    return 0;
}

/*----------------------------------------------------------------------------*/
int funcA (const char *str)
{
    if (!*str)
        return 0;

    Arglist A(256, 32);
    double d;
    bool help;
    int n;
    char c;

    ifstream ifs (str);  // use argument as file,
    istringstream istrs (str);             // or as a string

    A << '-' << KEEPUNSWITCHED;            // setup
	A.setversion("2.01");

    if (A.add ("h,H,help,HELP", "help arg", &help)
     || A.add ("d,double,float", "double arg", &d)
     || A.add ("n,numeric", "number", &n)
     || A.add ("c,character", "char", &c)
     || (!ifs.fail() && A (ifs) < 0)
     || (ifs.fail() && A (istrs) < 0)
     || A.numerrors() )
        return -1;

    if (help)
        A.mk_usagelong (cerr);

    print_results (A, A.numparsed());

    return A.numparsed();
}

int funcB (const char *str)
{
    if (!*str)
        return 0;

    Arglist B (8, 8);
    double d;
    bool help;
    int n;
    char c;
    ifstream ifs (str);  // use argument as file,
    istringstream istrs (str);             // or as a string

   B << (KEEPUNSWITCHED|NOPROMPT) << '-' <<  "grandchild values";
	B.setversion("3.01");

    if (B.add ("h,H,help,HELP", "", "", "help arg", &help)
     || B.add ("d,double,float", "double arg", &d)
     || B.add ("n,numeric", "number", &n)
     || B.add ("c,character", "char", &c)
     || (!ifs.fail() && B (ifs) < 0)
     || (ifs.fail() && B (istrs) < 0)
     || B.numerrors() )
        return -1;

    if (help)
        B.mk_usagelong (cerr);

    print_results (B, B.numparsed());

    return B.numparsed();
}

int funcC (const char *str)
{
    if (!*str)
        return 0;

    Arglist C (6);
    double d;
    bool help;
    int n;
    char c;
    ifstream ifs (str);  // use argument as file,
    istringstream istrs (str);             // or as a string

    C << (KEEPUNSWITCHED|USAGEONERROR) << '-' << "grandchild values";
	C.setversion("4.01");

    if (C.add ("h,H,help,HELP", "", "", "help arg", &help)
     || C.add ("d,double,float", "double arg", &d)
     || C.add ("n,numeric", "number", &n)
     || C.add ("c,character", "char", &c)
     || (!ifs.fail() && C (ifs) < 0)
     || (ifs.fail() && C (istrs) < 0)
     || C.numerrors() )
        return -1;

    if (help)
        C.mk_usagelong (cerr);

    print_results (C, C.numparsed());

    return C.numparsed();
}

/*----------------------------------------------------------------------------*/
void print_results (Arglist& argl, int argc)
{
    cerr << "Arguments paSsed: " << argc
         << ", Arguments paRsed: " << argl.numparsed() << '\n'
         << "Unswitched: " << argl.numunswitched()
         << ", Errors: " << argl.numerrors() << '\n';

    argl.pr_values(cerr);
    argl.pr_unsws(cerr) << '\n';
}

/*----------------------------------------------------------------------------*/
