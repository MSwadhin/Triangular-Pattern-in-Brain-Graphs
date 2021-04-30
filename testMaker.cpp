#include<bits/stdc++.h>
using namespace std;

struct Tuple{
    int u,v,w;
    Tuple(){}
    Tuple(int a,int b,int c){
        u=a,v=b,w=c;
    }
};

bool operator<(Tuple a,Tuple b){
    if(a.u==b.u){
        if(a.v==b.v)return a.w<b.w;
        return a.v<b.v;
    }
    return a.u < b.u;
}

vector<Tuple> TestTuples; // contains tuples for testing

void print(){
    ofstream outfile;
    outfile.open("OC100.txt");
    for(Tuple t:TestTuples){
        outfile<<t.u<<" "<<t.v<<" "<<t.w<<"\n";
    }
    outfile.close();
}


void takeTestTuples(int threshold){
    ifstream infile;
    infile.open("Occurrence.txt");
    while(!infile.eof()){
        string s;
        getline(infile, s);
        int u,v,w,oc;
        int id;
        sscanf( s.c_str(),"%d %d,%d,%d %d",&id,&u,&v,&w,&oc );
        if(oc >= threshold){
            TestTuples.push_back( Tuple(u,v,w) );
        }
    }
    infile.close();
}


int main(){


    takeTestTuples(300);
    cerr<<(int)TestTuples.size()<<endl;
    print();

    return 0;
}