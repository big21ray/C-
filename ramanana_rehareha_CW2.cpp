#include <map>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
using namespace std;



vector<vector<double> > init_box(int i, int j);
void print(vector<vector<double> > mat);
vector<vector<double> > init_exo();
bool check(double p);
bool simulate(double p);

bool check_pos_lower(int x,int y);
bool check_pos_higher(int x,int y);
vector<vector<double> > transition(vector<vector<double> > mat, double p);
bool check_layer(vector<vector<double> > mat, int y);

class Point{

    public:
    int x;
    int y;
    bool isS;

    Point(int pointX,int pointY){
        x = pointX;
        y = pointY;
        isS = true;
    }
    Point(int pointX, int pointY,bool S){
        x = pointX;
        y = pointY;
        isS = S;

    }




};

class Skyline{
    public:
        vector<Point> sky;
        Skyline(){}
        Skyline(Point p){
            sky.push_back(p);
        }
        void add(Point p)  ;
        void print();
        void pop();
        Skyline getSkyline();
        void sort();

    };

void Skyline::add(Point p){
    sky.push_back(p);

}

void Skyline::print(){
    int n = sky.size();
    for(int i = 0; i<n;i++){
        cout<< sky[i].x << sky[i].y<<" "<< sky[i].isS << endl;
    }


}





void Skyline::sort(){
    Point temp = Point(sky[0].x,sky[0].y);
    int i,j;
    int n = sky.size();

    for(i =0;i<n; i++){
        for(j=i; j<n;j++){

            if(sky[j].x<sky[i].x){
                temp = sky[i];
                sky[i] = sky[j];
                sky[j] = temp;
            }
        }
    }


}

void Skyline::pop(){

    sky.pop_back();
}


Skyline Skyline::getSkyline(){

    Skyline output;
    int max_prio = 0;
    int max = 0;
    int n = sky.size();
    vector<int> prio {0};

    int i =0;
    output.add(Point(sky[0].x,0));


    while(i<n){
        Point p = sky[i];


        if(sky[i].isS == 1){
            prio.push_back(sky[i].y);
            max_prio = *std::max_element(prio.begin(),prio.end());

            if(max != max_prio){
                output.add(Point(sky[i].x,max_prio));
                max = max_prio;
                i++;


            }
            else{
                i++;
            }

        }
        else{
            int y = sky[i].y;
            int compt = 0;
            while(prio[compt]!= y){
                compt++;
            }
            prio.erase(prio.begin()+compt);
            max_prio = *std::max_element(prio.begin(),prio.end());

            if(max != max_prio){
                output.add(Point(sky[i].x,max_prio));
                max = max_prio;
                i++;


            }
            else{
                i++;
            }

        }

    }
    return output;





}

int main(){
    int input;
    cout <<"Enter which exercice you want to do :"<< endl;
    cin>> input;
    if(input == 1){
        double p;

        checkk:
        cout<<"Enter the probability p:"<<endl;
        cin>>p;
        if(check(p) == false){
            goto checkk;
        }
        vector<vector<double> > mat = init_exo();

        int y = 0;


        transi:
        if(y<=59){
            if(check_layer(mat,y) == true){
                mat = transition(mat,p);
                y++;
                print(mat);
                cout<<endl;
                goto transi;

            }
        }
        if(y == 59){
            cout<<"We reached the final layer, the minimum probability seems to be around 0.525"<<endl;
        }
        else{
            cout<<"We haven't reached the final layer"<<endl;
        }

    }
    else{
        Skyline inp;
        int compteur = 1;
        ifstream fin("skyline.in");
        if (! fin.is_open()) {
        cout << "Error opening input file." << endl;
        return -1;
        }
        int number;
        int x;
        int y;

        while( fin.peek() != EOF )
        {
            fin >> x;
            fin >> y;
            if(compteur %2 == 1){

                Point p(x,y,true);
                compteur++;
                inp.add(p);

            }
            else{

                Point p(x,y,false);
                compteur++;
                inp.add(p);
            }

        }
        inp.pop();
        //inp.print();
        fin.close();
        Skyline outp ;
        inp.sort();
        outp = inp.getSkyline();



        ofstream fout("skyline.out");
        if (! fout.is_open()) {
            cout << "Error opening output file." << endl;
        return -1;
        }

        int n = outp.sky.size();
        for(int j = 0; j<n;j++){
            fout<<outp.sky[j].x<<" "<< outp.sky[j].y<<endl;
        }

        fout.close();



        fin.close();

        // close ifstream fin
        return 0;






    }






    return 0;

}


bool check(double p){

    if(p>=1 | p<=0){
        return false;
    }
    return true;
}


bool check_pos_lower(int x,int y){
    if(x<1 | y>59){
        return false;
    }
    return true;
}


bool check_pos_higher(int x,int y){
    if(x>79 | y>59){
        return false;
    }
    return false;
}

bool simulate(double p)
{


    double proba;
    srand(time(NULL));
    proba = rand() /(double)RAND_MAX;
    if (p >= proba){
        return true;
    }
    else{
        return false;
    }


}

vector<vector<double> > transition(vector<vector<double> > mat, double p){
    for(int i = 0; i<=79;++i){
        for(int j=0;j<=59;++j){
            if(mat[i][j] == 1){
                if(check_pos_lower(i,j) & simulate(p))
                {
                    mat[i-1][j+1] = 1;
                }
                if(check_pos_higher(i,j) & simulate(p)){
                    mat[i+1][j+1] = 1;
                }
        }
    }
    }
    return mat;
}

bool check_layer(vector<vector<double > > mat, int y){
    bool test = false;
    for(int i = 0;i<=79;i++){
        if(mat[i][y] == 1){
            test = true;
            return test;
        }

    }
    return test;
}


vector<vector<double> > init_box(int i, int j){


    int nrows = i, ncolumns = j;
    vector<vector<double> > mat; // note the space in ’> >’ !
    vector<double> row(ncolumns); // row = (0,0,0)
    mat.insert(mat.begin(), nrows, row); // mat = (row,row,row,row)
    return mat;
}


vector<vector<double> > init_exo(){
    vector<vector<double> > mat = init_box(80,60);
    for(int i = 19; i< 60; ++i){
        if((i+1)%2 == 1){
            mat[i][0] =1;
        }
    }
    return mat;
}



void print(vector<vector<double> > mat){

    for (int i=0; i<mat.size(); ++i) {
    for (int j=0; j<mat[i].size(); ++j) cout << mat[i][j];
    cout << endl;
    }
}
