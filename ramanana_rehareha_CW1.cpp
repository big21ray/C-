#include <map>
#include <iostream>
#include<vector>
#include<math.h>
using namespace std;




bool checkPrime(int p);
vector<int> computePrimes(int p);
int nthPrime(int n);

vector<int> createStack(int k);
vector<int> shuffleStack(vector<int> v);
vector<int> shuffleStackm(vector<int> v,int m);
void printTab(vector<int> v);
vector<int> fullShuffle(int k);
vector<int> fullShuffleFreq(int k);
int argMax(vector<int> v);

vector<int> bestCard(vector<int> v);
vector<int> fromFreq(vector<int> freq,int k);
int firstTop(int d,int k);
int howmanyTop(int d, int k);

int main(){
    int p;
    int input;
    int input2;
    bool check;
    cout<<"Choose what this program does"<<endl;
    cout<<"1) Check if your input is a prime"<<endl;
    cout<<"2) Compute all the prime number inferior or equal to your input"<<endl;
    cout<<"3) Compute the nth prime or number, or the first n prime number"<<endl;
    cout<<"4) Exercice 2"<<endl;;
    cout<<"5) Quit the program"<<endl;
    cout<<"Type your choice:  1,2,3,4 or 5:"<<endl;
    label:
    cin>>p;


    if(p==1){
        cout<<endl;
        cout<< "Enter your input"<<endl;
        cin>>input;
        cout<<endl;
        check = checkPrime(input);
        if(check ==1){
            cout<<"Your input is a prime number"<<endl;
        }
        else{
            cout<<"Your input is not a prime number"<<endl;
        }

    }
    else if(p==2){
        cin>>input;
        vector<int> v = computePrimes(input);
        int n = v.size();
        cout<<"The prime numbers inferior to "<< input<<" are:"<<endl;
        for(int i = 0; i < n; i++){
            cout<<v[i]<<endl;
        }

    }
    else if(p==3){
        cin>>input;
        int nth = nthPrime(input);
        cout<<nth<<endl;

    }
    else if(p==5){
        return 0;
    }

    else if(p==4){
        cout<<"Enter the size of the stacks, i.e., your k"<<endl;
        cin>> input;
//        cout<<"Enter the the size of the shuffle, i.e., your m"<<endl;
//        cin>> input2;
//        cout<<endl;
//        vector<int> v = createStack(input);
//        vector<int> sh = shuffleStackm(v,input2);
        vector<int> sh = fullShuffle(input);
        cout<<"The shuffled stack is equal to: "<<endl<<endl;
        printTab(sh);
        cout<<endl;
        cout<<endl;

        cout<<"Question a : As said in the paper, we find "<<sh[0]<<" "<<sh[1]<<" and "<< sh[2]<<" "<<endl<<endl;
        cout<<"Question b : Here are the cards that are on top the most : ";
        vector<int> freq;
        freq = fullShuffleFreq(input);
        freq = fromFreq(freq,input);

        vector<int> ret = bestCard(freq);
        printTab(ret);
        cout<<endl<<endl;
        int d = sh[0];
        int quesC = firstTop(d,input);
        cout<<"Question c : The topmost card from (a) was on top for the first time at the shuffle number : " << quesC <<endl;
        cout<<endl;

        int quesD = howmanyTop(d,input);
        cout<<"Question d : The topmost card from (a) was on top " << quesD <<" times"<< endl;
        cout<<endl;


        return 0;



    }
    else{
        cout<<"Enter a correct answer"<<endl;
        goto label;
    }







    return 0;


}

bool checkPrime(int p){
   bool check = 1;
   float q;
   q = sqrt(p);
   int r;
   for(int i = 2; i<=q; i++) {
       r = p % i;

       if(r == 0){
           check = 0;
           return check;

       }
   }
   return check;
}

vector<int> computePrimes(int p){
    int compteur = p;
    vector<int> v;
    for(int i = 2; i<= compteur; i++){
        if(checkPrime(i)){
            v.push_back(i);
        }
    }
    return v;
}

int nthPrime(int n){
    int compteur = 0;
    int i = 2;
    int last;
    while(compteur<n){
        if(checkPrime(i)){
            compteur++;
            last = i;
        }
        i++;

    }
    return last;

}

vector<int> createStack(int k){
    vector<int> v;
    if(k<2){
        cout<<" k has to be superior or equal to 2"<<endl;
        return v;
    }
    else{
        for(int i=1;i<=2*k;i++){

            v.push_back(i);


        }
        return v;
    }
}

vector<int> shuffleStack(vector<int> v){
    int n = v.size();
    int k = n/2;
    vector<int> v_plus;
    vector<int> v_moins;
    vector<int> fin;
    for(int i = 0; i<n;i++){
        if(i<= k-1){
            v_moins.push_back(i+1);
        }
        else{
            v_plus.push_back(i+1);
        }
    }
    int j = 0;
    int compteur = 0;
    while(j<n){
        if(j%2 ==0){
            fin.push_back(v_plus[compteur]);
            j++;
        }
        else{
            fin.push_back(v_moins[compteur]);
            compteur++;
            j++;
        }
    }

    return fin;

}

vector<int> shuffleStackm(vector<int> v,int m){

    int n = v.size();
    vector<int> v_plus;
    vector<int> v_moins;
    vector<int> fin;
    for(int i = 0; i<m;i++){
        v_moins.push_back(v[i]);
    }
    for(int c = m; c<2*m;c++){
        v_plus.push_back(v[c]);
    }
    int j = 0;
    int compteur = 0;
    while(j<2*m){
        if(j%2==0){
            fin.push_back(v_plus[compteur]);
            j++;
        }
        else{
            fin.push_back(v_moins[compteur]);
            compteur++;
            j++;
        }
    }
    if(n-2*m > 0){
        for(int p = 2*m ; p<n;p++){
            fin.push_back(v[p]);
        }
    }

    return fin;

}


void printTab(vector<int> v){
    int n = v.size();
    for(int i = 0;i<n ; i++){
        cout<<v[i]<<" ";


    }
}


vector<int> fullShuffle(int k){
    vector<int> v = createStack(k);
    vector<int> freq = createStack(k);

    int compteur = 1;
    int p ;
    int n = freq.size();
    for(int i = 0; i<n ; i++){
        freq[i] = 0;
    }
    while(compteur<= k){
            v = shuffleStackm(v,compteur);
            p = v[0];
            freq[p]++;
            compteur++;


        }



    return v;
}


vector<int> fullShuffleFreq(int k){
    vector<int> v = createStack(k);
    vector<int> freq = createStack(k);
    vector<int> result;

    int compteur = 1;
    int p ;
    int n = freq.size();

    while(compteur<= k){
            v = shuffleStackm(v,compteur);
            result.push_back(v[0]);

            compteur++;


        }
    return result;
}

int argMax(vector<int> v){

    int max = v[0];
    int argMax = 0;
    int n = v.size();
    vector<int> arg;

    for(int i = 0; i<n; i++){
        if(v[i]>max){
            max = v[i];
            argMax = i;
        }

    }
    return argMax;


}

vector<int> fromFreq(vector<int> freq,int k){
    int n = freq.size();
    vector<int> fromFreq(2*k,0);
    for (int i = 0; i<n ; i++){

        int dep = freq[i];
        dep--;
        fromFreq[dep]+=1;



    }
    return fromFreq;
}





vector<int> bestCard(vector<int> v){

    vector<int> result;
    int ret = argMax(v);
    v[ret] = 0;
    ret++;
    result.push_back(ret);

    ret = argMax(v);
    v[ret] = 0;
    ret++;
    result.push_back(ret);

    ret = argMax(v);
    v[ret] = 0;
    ret++;
    result.push_back(ret);

    return result   ;



}

int firstTop(int d,int k){
    vector<int> v = createStack(k);
    int res = 0;

    int compteur = 1;
    while(compteur<= k){
            v = shuffleStackm(v,compteur);
            if(v[0]==d){
                res = compteur;
                break;
               }


            compteur++;


        }
    return res;
}

int howmanyTop(int d,int k){
    vector<int> v = createStack(k);
    int res = 0;

    int compteur = 1;
    while(compteur<= k){
            v = shuffleStackm(v,compteur);
            if(v[0]==d){
                res++;

               }


            compteur++;


        }
    return res;
}

