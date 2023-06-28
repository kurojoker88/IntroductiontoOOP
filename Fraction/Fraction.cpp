#include <iostream>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n----------------------------------------\n"

class Fraction
{
    int integer;
    int numerator;
    int denominator;
public:
    int get_integer()const
    {
        return integer;
    }
    int get_numerator()const
    {
        return numerator;
    }
    int get_denominator()const
    {
        return denominator;
    }

    void set_integer(int integer)
    {
        this->integer = integer;
    }
    void set_numerator(int numerator)
    {
        this->numerator = numerator;
    }
    void set_denominator(int denominator)
    {
        if (denominator == 0)denominator = 1;
        this->denominator = denominator;
    }

    // Constructor
    Fraction()
    {
        this->integer = 0;
        this->numerator = 0;
        this->denominator = 1;
        cout << "DefaultConstruct:\t" << this << endl;
    }
    Fraction(int integer)
    {
        this->integer = integer;
        this->numerator = 0;
        this->denominator = 1;
        cout << "1ArgConstructor:\t" << this << endl;

    }
    Fraction(int numerator, int denominator)
    {
        this->integer = 0;
        this->numerator = numerator;
        set_denominator(denominator);
        cout << "2ArgConstructor:\t" << this << endl;

    }
    Fraction(int integer, int numerator, int denominator)
    {
        this->integer = integer;
        this->numerator = numerator;
        set_denominator(denominator);
        cout << "Constructor:\t" << this << endl;
    }
    Fraction(const Fraction& other)
    {
        this->integer = other.integer;
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        cout << "CopyConstructor:\t" << this << endl;

    }

    ~Fraction()
    {
        cout << "Destructor:\t" << this << endl;
    }

    Fraction& operator=(const Fraction& other) // перегрузить арифметические операторы
    {
        this->integer = other.integer;
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        cout << "CopyAssignment:\t" << this << endl;
        return *this;
    }

    void to_proper()
    {
        /* My solution
        while (numerator >= denominator)
        {
            if (numerator >= denominator)
            {
                numerator = numerator - denominator;
                integer++;
            }
        }*/
        integer += numerator / denominator;
        numerator %= denominator;
    }

    void to_improper() 
    {
        /* My solution
        if (integer != 0 || denominator >= numerator)
        {
            numerator = integer * denominator + numerator;
            integer = 0;
        }*/
        numerator += integer * denominator;
        integer = 0;
    }

    void reduce() 
    {
        /*int n;
        if (numerator < denominator) n = numerator;
        else {n = denominator;}
        for (int i = n; i > 0; i--)
        {
            if (numerator % i == 0 && denominator % i == 0)
            {                
                numerator = numerator / i;
                denominator = denominator / i;             
            }            
        }*/
    }
        
    void print()const
    {
        if (integer)cout << integer;
        if (numerator)
        {
            if (integer)cout << "(";
            cout << numerator << "/" << denominator;
            if (integer)cout << ")";
        }
        else if (integer == 0)cout << 0;
        cout << endl;
    }
};

Fraction& operator+(const Fraction& left, const Fraction& right)
{
    Fraction result;
    int numer1;
    int numer2;
    result.set_integer(left.get_integer() + right.get_integer());
    if (left.get_denominator() == right.get_denominator())
    {
        result.set_numerator(left.get_numerator() + right.get_numerator());
        result.set_denominator(left.get_denominator() + right.get_denominator());
    }
    else
    {
        numer1 = left.get_numerator() * right.get_denominator();
        numer2 = right.get_numerator() * left.get_denominator();
        result.set_numerator(numer1 + numer2);
        result.set_denominator(left.get_denominator()* right.get_denominator());
    }
    result.reduce();
    result.to_proper();
    cout << "Sum:\t";
    result.print();
    cout << endl;
    return result;
}

Fraction& operator-(const Fraction& left, const Fraction& right)
{
    Fraction result;
    Fraction copyleft = left;
    Fraction copyright = right;
    int numer1;
    int numer2;
    copyleft.to_improper();
    copyright.to_improper();

    if (copyleft.get_denominator() == copyright.get_denominator())
    {
        result.set_numerator(copyleft.get_numerator() - copyright.get_numerator());
        result.set_denominator(copyleft.get_denominator());
    }
    else
    {
        numer1 = copyleft.get_numerator() * copyright.get_denominator();
        numer2 = right.get_numerator() * copyleft.get_denominator();
        result.set_numerator(numer1 - numer2);
        result.set_denominator(copyleft.get_denominator() * copyright.get_denominator());
    }

    result.reduce();
    result.to_proper();
    cout << "Difference:\t";
    result.print();
    cout << endl;
    return result;
}

Fraction& operator*(const Fraction& left, const Fraction& right)
{
    Fraction result;
    Fraction copyleft = left;
    Fraction copyright = right;
    copyleft.to_improper();
    copyright.to_improper();

    result.set_numerator(copyleft.get_numerator() * copyright.get_numerator());
    result.set_denominator(copyleft.get_denominator() * copyright.get_denominator());
    result.reduce();
    result.to_proper();
    cout << "Multiply:\t";
    result.print();
    cout << endl;
    return result;
}

Fraction& operator/(const Fraction& left, const Fraction& right)
{
    Fraction result;
    Fraction copyleft = left;
    Fraction copyright = right;
    copyleft.to_improper();
    copyright.to_improper();

    result.set_numerator(copyleft.get_numerator() * copyright.get_denominator());
    result.set_denominator(copyleft.get_denominator() * copyright.get_numerator());
    result.reduce();
    result.to_proper();
    cout << "Division:\t";
    result.print();
    cout << endl;
    return result;
}
//#define CONSTRUCTOR_CHECK
void main()
{
    setlocale(LC_ALL, "");
#ifdef CONSTRUCTOR_CHECK
    Fraction A;
    A.print();

    Fraction B = 5;
    B.print();

    Fraction C(1, 2);
    C.print();
    
    Fraction D(2, 3, 4);
    D.print();

    Fraction E = C;
    E.print();

    Fraction F;
    F = D;
    F.print();
#endif CONSTRACTOR_CHECK
    Fraction A(2, 3, 4);
    A.print();

    A.to_improper();
    A.print();

    Fraction B(3, 4, 5);
    B.print();

    B.to_proper();
    B.print();

    Fraction C(4, 2, 6);
    C.print();

    C.reduce();
    C.print();
    cout << delimiter << endl;
    cout << delimiter << endl;

    Fraction S = A + B;
    S.print(); 
    cout << delimiter << endl;
    
    Fraction D = A - B;
    D.print();
    cout << delimiter << endl;

    Fraction M = A * B;
    M.print();
    cout << delimiter << endl;

    Fraction Dv = A / B;
    Dv.print();
    cout << delimiter << endl;
}

