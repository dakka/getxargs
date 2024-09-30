#include <iomanip>
#include <argument.h>

bool Xflag;
int func0(), func2(const char *);
void print_results (Arglist& , int);

int main (int argc, char *argv[])
{
    double d1;
    int n;
    char c;
    bool b, shorthelp, longhelp, print, alt;
    char *str;

    Arglist argl (32, 128);
    argl << KEEPUNSWITCHED << '-' << OVERWRITE << "[unswitched values]";
	argl.setversion("1.15");


    if (argl.add ("h,H,help,HELP", "", "?", "print long usage", &longhelp)
     || argl.add ("?", "", "h", "switch summary", &shorthelp)
     || argl.add ("d,double,float,doubleprecision", "double value", &d1)
     || argl.add ("s,string,S,STRING", "string", &str, "hello")
     || argl.add ("b,boolean,onoff,switch", "boolean value", &b)
     || argl.add ("alt,altern", "sub-string test,boolean value", &alt)
     || argl.add ("p,print", "print parsed values", &print)
     || argl.add ("X,XFLAG", "dynamic boolean switch", &Xflag)
     || argl.add ("n,numeric,i,integer", "numeric value", &n, 35)
     || argl.add ("c,character,byte", "character value", &c, 'X')
     || argl.add ("f,function", "XFLAG","","calls func0", func0)
     || argl.add ("FUNC,FUNCTION", "calls func2 with value", func2))
    {
        cerr << "error: Arglist::add" << endl;
        return 2;
    }
    else if (argl (argc, argv) < 0 || argl.numerrors() || longhelp )
    {
        argl.mk_usagelong (cerr);
        return 1;
    }

    if (shorthelp)
        argl.mk_usageshort (cerr);

    if (print)
        print_results (argl, argl.numparsed());

    return 0;
}

/*----------------------------------------------------------------------------*/
int func0 ()
{
    static int i(0);

    cout << ++i << ":hello from func0(), Xflag: " << boolalpha << Xflag << endl;
    return Xflag;
}

/*----------------------------------------------------------------------------*/
int func2 (const char *str)
{
    int i(0);
    istringstream istr (str);

    istr >> i;
    for (; i; --i)
        cout << "f2(" << i << "); ";
    cout << endl;
    return 0;
}

/*----------------------------------------------------------------------------*/
void print_results (Arglist& argl, int argc)
{
    cerr << ": Arguments paSsed: " << argc
         << ", Arguments paRsed: " << argl.numparsed() << endl
         << "Unswitched: " << argl.numunswitched()
         << ", Errors: " << argl.numerrors() << endl;

    argl.pr_values(cerr);
    argl.pr_unsws(cerr) << endl;
}

/*----------------------------------------------------------------------------*/
