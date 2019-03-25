#include <map>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
using namespace std;

class fraction {
    friend ostream &operator<< (ostream &os, const fraction &f){
        if(f.denominator != 1){

            cout<<f.numerator<<"/"<<f.denominator<<endl;
        }
        else{
            cout<<f.numerator<<endl;
        }

    }

    private:
        int numerator, denominator;
        void reduce();
    public:
        int get_num();
        int get_denom();

        fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { reduce(); }




        fraction operator+ (const fraction &f) const;
        fraction &operator+= (const fraction &f);
        fraction operator* (const fraction &f) const;
        fraction &operator*= (const fraction &f);
        fraction operator/ (const fraction &f) const;
        fraction &operator/= (const fraction &f);
        fraction operator- (const fraction &f) const;
        fraction &operator-= (const fraction &f);
        operator double(){
            double p;
            p = (double)numerator/(double)denominator;
            return p;
        }



        bool operator< (const fraction &f) const;
        fraction operator- () const { fraction res(-numerator, denominator); return res; }
};




int fraction::get_denom(){
    return denominator;

}

int fraction::get_num(){
    return numerator;
}

int pgcd(int a, int b);

bool fraction::operator<(const fraction &f) const{
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;

    if((c*b - a*d) < 0){
        return true;
    }
    else{
        return false;
    }


}




fraction& fraction::operator*=(const fraction &f){
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = a*c;
    denom = b*d;
    fraction temp(num,denom);
    *this = temp;

}

fraction fraction::operator* (const fraction &f) const{
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = a*c;
    denom = b*d;
    fraction temp(num,denom);
    return temp;
}




fraction& fraction::operator-=(const fraction &f){
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = c*b - a*d;
    denom = b*d;
    fraction temp(num,denom);
    *this = temp;

}

fraction fraction::operator- (const fraction &f) const{
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = c*b - a*d;
    denom = b*d;
    fraction temp(num,denom);
    return temp;
}
fraction& fraction::operator/=(const fraction &f){
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = b*c;
    denom = a*d;
    fraction temp(num,denom);
    *this = temp;

}

fraction fraction::operator/ (const fraction &f) const{
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = b*c;
    denom = a*d;
    fraction temp(num,denom);
    return temp;
}




fraction& fraction::operator+=(const fraction &f){
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = a*d + b*c;
    denom = b*d;
    fraction temp(num,denom);
    *this = temp;

}

fraction fraction::operator+ (const fraction &f) const{
    int a = f.numerator;
    int b = f.denominator;
    int c = this->numerator;
    int d = this->denominator;
    int num;
    int denom;
    num = a*d + b*c;
    denom = b*d;
    fraction temp(num,denom);
    return temp;

}

int pgcd(int a , int b )

{   if(a == 0){
        return 1;
    }
    else{
    int r = 0;
    // il faut a > b
    if(a < b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    if(a <b)
        std::swap(a, b);

    if((r = a%b) == 0)
        return b;
    else
        return pgcd(b, r);
    }
}





void fraction::reduce(){
    int r;
    r = pgcd(numerator,denominator);
    numerator = numerator/r;
    denominator = denominator/r;
    if(denominator<0){
        numerator=-numerator;
        denominator = -denominator;
    }



}

int main(){

    fraction a(12,6),b(1,25);
    fraction d;
    bool g = a<b;

    cout<< double(b)<<endl;;
}
