#include <iostream>
#include<vector>
#include<complex>
#include<cmath>
#include<algorithm>

using namespace std;
int N = 10000, K = 4000;

template<typename T>
class mathvector {
public:

    vector<T> vec;


    void push_back(T a){
        vec.push_back(a);
    }
    void set_vector(const vector<T> &p) {
        vec = p;
    }

    void set_index(int i, T r) {
        vec[i] = r;
    }

    T get_index(int i) const {
        return vec[i];
    }

    vector<T> const get_vector() const {
        return vec;
    }

    mathvector(const vector<T> &p)  {
        set_vector(p);

    }

    mathvector() {


    }
    void normalize(){
        int n = vec.size();
        T p = 0;
        for(int i = 0; i<n ; ++i){
            p+=vec[i]*vec[i];
        }
        double q = (double) p;
        q = sqrt(q);
        p = (T) q;
        if(p!=0) {
            for (int i = 0; i < n; ++i) {
                vec[i] = vec[i] / p;
            }
        }
        else{
        }
    }



    mathvector<T> operator=(const mathvector<T> &y) {
        vector<T> d = y.get_vector();
        set_vector(d);
        return *this;

    }

    mathvector<T> operator+(const mathvector<T> &y) {
        vector<T> d = y.get_vector();
        for (int i = 0; i < N; ++i) {
            vec[i] += d[i];
        }

        return *this;

    }

    mathvector<T> operator-(const mathvector<T> &y) {
        vector<T> d = y.get_vector();
        for (int i = 0; i < N; ++i) {
            vec[i] -= d[i];
        }

        return *this;

    }

    mathvector<T> operator+=(const mathvector<T> &y) {
        vector<T> d = y.get_vector();
        for (int i = 0; i < N; ++i) {
            vec[i] += d[i];
        }

        return *this;

    }

    mathvector<T> operator-=(const mathvector<T> &y) {
        vector<T> d = y.get_vector();
        for (int i = 0; i < N; ++i) {
            vec[i] += d[i];
        }

        return *this;

    }

    mathvector<T> operator*(const T &r) {

        for (int i = 0; i < N; ++i) {
            vec[i] *= r;
        }

        return *this;

    }

    mathvector<T> operator*=(const T &r) {

        for (int i = 0; i < N; ++i) {
            vec[i] *= r;
        }

        return *this;

    }
    T operator*(const mathvector<T> &p) const {

        T j = (T) 0;
        int n = p.vec.size();
        for (int i = 0; i < n; ++i) {



                j = j + (T) vec[i]*p.get_index(i);






        }
        return j;


    }

    friend ostream &operator <<(ostream &os, mathvector<T> &p){
        int m = p.vec.size();
        int i = 0;
        while (i<m){
            os << p.get_index(i)<< " ";

            ++i;


        }
        return os;


    }



};




template<typename T>
class mathmatrix {

public:

    virtual mathvector<T> operator*(const mathvector<T> &y) {};

    virtual void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) {};

    virtual T power_method(const mathvector<T> &, int i) {};


};






template<typename T>
class fullmatrix : public mathmatrix<T> {
public :

    vector<vector<T> > vec;

    fullmatrix(const vector<vector<T> > &vec1) {
        vec = vec1;
    }
    vector<vector<T> > get_vec(){
    return vec;
}

    T get_index(int i, int j) const {

        return(vec[i][j]);
    }
    friend ostream &operator <<(ostream &os, const fullmatrix<T> &p){
        for(int i = 0; i<N;++i){
            for(int j = 0; j<N;++j){
                cout<<p.get_index(i,j);
            }
            cout<<endl;
        }
    }

    fullmatrix() {
        vector<vector<T> > row;
        vector<T> l;
        for (int i = 0; i < N; ++i) {
            l.push_back((T) 0);
        }
        for (int i = 0; i < N; ++i) {
            row.push_back(l);
        }
        vec = row;
    }

    fullmatrix operator + (const T &p){
        int n = vec.size();

        for(int i = 0; i<n; ++i){
            vec[i][i] += p;
        }
        return *this;
    }
    void operator += (const T &p){
        int n = vec.size();

        for(int i = 0; i<n; ++i){
            vec[i][i] += p;
        }

    }

    fullmatrix operator - (const T &p){
        int n = vec.size();

        for(int i = 0; i<n; ++i){
            vec[i][i] -= p;
        }
        return *this;
    }
    void operator -= (const T &p){
        int n = vec.size();

        for(int i = 0; i<n; ++i){
            vec[i][i] -= p;
        }

    }

    mathvector<T> operator * (const mathvector<T> &y) const {
        vector<T> out ;
        vector<T> in = y.vec;
        int n = y.vec.size();


        for (int i = 0; i < n; ++i) {
            T p = (T) 0;
            for (int j = 0; j < N; ++j) {
                p += vec[i][j] * in[j];
            }

            out.push_back(p);
        }
        mathvector<T> output(out);
        return output;


    }

    void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) {
        int n = x.vec.size();


        for (int i = 0; i < n; ++i) {

            y.vec[i] =  this->get_index(i,0)*x.get_index(0);
            for (int j = 1; j < n; ++j) {


                y.vec[i] += this->get_index(i,j)*x.get_index(j);
            }


        }
    }

    T power_method(const mathvector<T> &x, int K){

        mathvector<T> q;
        mathvector<T> z;
        q = x;
        q.normalize();
        for(int j = 0; j<K;++j){
            z = (*this)*q;


            q = z;
            q.normalize();


        }
        mathvector<T> p = q;

        mathvector<T> g = (*this)*p;
        T u = q*g;
        return u;



    }


};


template<typename T>
class CW5_matrix : fullmatrix<T> {
public:
    vector<vector<T> > vec;

    CW5_matrix(int N){
        fullmatrix<T> A = fullmatrix<T>();
        vec = A.get_vec();
        vec[0][0] = (T) 2;
        vec[N-1][N-1] = (T) 2;
        vec[N-1][N-2] = (T) -1;

        for(int i =1;i<N-1 ;++i){
            vec[i][i] = (T) 2;
            vec[i][i+1] = (T) -1;
            vec[i][i-1] = (T) -1;
        }
        vec[N-1][0] = (T) -1;
        vec[0][N-1] = (T) -1;
        vec[0][1] = (T) -1;



    }
    T get_index(int i,int j){
        return(vec[i][j]);
    }
    friend ostream &operator <<(ostream &os, const CW5_matrix<T> &p){
        for(int i = 0; i<N;++i){
            for(int j = 0; j<N;++j){
                cout<<p.get_index(i,j);
            }
            cout<<endl;
        }
    }

    mathvector<T> operator * (const mathvector<T> &y) const {
        vector<T> out ;
        vector<T> in = y.vec;

        for (int i = 0; i < N; ++i) {
            T p = (T) 0;
            for (int j = 0; j < N; ++j) {
                p += vec[i][j] * in[j];
            }

            out.push_back(p);
        }
        mathvector<T> output(out);
        return output;


    }


    T power_method(const mathvector<T> &x, int K){
        T norm =  x*x;

        mathvector<T> q;
        mathvector<T> z;
        q = x;
        q.normalize();
        for(int j = 0; j<K;++j){
            z = (*this)*q;



            q = z;
            q.normalize();


        }
        mathvector<T> p = q;

        mathvector<T> g = (*this)*p;
        T u = q*g;
        return u;



    }





};


template<typename T>
class diagmatrix : public mathmatrix<T> {
public :

    vector<T> vec;

    diagmatrix(const vector<T> &vec1) {
        vec = vec1;
    }
    T get_index(int i) const{
        return(vec[i]);
    }

    friend ostream &operator <<(ostream &os, const mathmatrix<T> &p){


        for(int i = 0; i<N;++i){
            for(int j = 0; j<N;++j){
                if(j<i){
                    cout<<"0";
                }
                if(j==i){
                    cout<<p.get_index(i);

                }
                else {
                    cout << "0";
                }

            }
            cout<<endl;


        }
    }

    diagmatrix() {
        vector<T> l;
        for (int i = 0; i < N; ++i) {
            l.push_back((T) 0);
        }

        vec = l;
    }
    diagmatrix operator + (const T &p) const{
        for(int i = 0; i<vec.size();++i){
            vec[i] += p;
        }
        return *this;
    }

    void operator += (const T &p) const {
        for(int i = 0; i<vec.size();++i){
            vec[i] += p;
        }

    }
    diagmatrix operator - (const T &p) const{
        for(int i = 0; i<vec.size();++i){
            vec[i] -= p;
        }
        return *this;
    }

    void operator -= (const T &p) const{
        for(int i = 0; i<vec.size();++i){
            vec[i] -= p;
        }

    }

    mathvector<T> operator*(const mathvector<T> &y) {
        for(int i = 0; i<N; ++i){

            vec[i]*= y.get_index(i);
        }
        mathvector<T> output(vec);
        return output;


    }

    void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) {
        int n = x.vec.size();


        for (int i = 0; i < n; ++i) {
            y.set_index(i, vec[i] * x.get_index(i));



        }
    }

    T power_method(const mathvector<T> &x, int K){
        auto it = max_element(begin(vec), end(vec));
        return( *it) ;
}


};


int main() {
    int N = 10000, K = 10;
    mathvector<double> x_a;
   for (int i = 0; i < N; i++)
   {
       x_a.push_back(i+1); // x = (1,2,...,N)^T
   }
   //cout<< x_a <<endl;

   double a = x_a*x_a;

    CW5_matrix<double> A(N);
    double lambda = A.power_method(x_a, K);
   //cout << "largest lambda (in modulus) for A = " << lambda << endl;


    double b[] = {1.0, 1.0, 1.0, 1.0};
    vector<double> vb(b, b+4);

    mathvector<double> x_b(vb); // x = (1,1,1,1)^T
    cout << " x . x = " << x_b * x_b << endl;

    double r1[] = {3.0, 1.0, 2.0, 5.0}, r2[] = {1.0, 1.0, 3.0, 7.0},
            r3[] = {2.0, 3.0, 2.0, 4.0}, r4[] = {5.0, 7.0, 4.0, 2.0};


    vector<double> row1(r1, r1+4), row2(r2, r2+4), row3(r3, r3+4), row4(r4,r4+4);
    vector<vector<double> > BB;
    BB.push_back(row1); BB.push_back(row2); BB.push_back(row3); BB.push_back(row4);


    fullmatrix<double> B(BB); // matrix B
    B.y_eq_Ax(x_a, x_b);
    //cout << x_a << endl; // y = B * x
    //cout<<x_b<<endl;

    lambda = B.power_method(x_b, K);
    //cout<<"lambda value is " << lambda<<endl;

    B -= lambda; // B = B - lambda * Id



    double l2 = B.power_method(x_b, K);

    B += lambda; // B = B + lambda * Id
    cout << "The spectrum of B lies between " << lambda << " and " << l2 + lambda << endl;
    diagmatrix<double> D(row4);
    lambda = D.power_method(x_b, K);
    cout << "largest lambda (in modulus) for D = " << lambda << endl;

}