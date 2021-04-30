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

vector<Tuple> AllTuples; // Contains All Possible Tuples
vector<int> occurs;

map<Tuple,int> mp;


void process(int graph[185][185]){ // Given Adjacency Matrix

    int n = 180;

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if( graph[i][j] && graph[j][i])
            for(int k=j+1;k<=n;k++){
                if( graph[j][k] && graph[k][j] ){
                    if( graph[i][k] && graph[k][i] ){
                        Tuple t(i,j,k);
                        int id = mp[t];
                        occurs[id]++;
                    }
                }
            }
        }
    }
}



void readFile(int id){// Read Graph From ith File
    ifstream infile;
    string s = "graph_connectome_";
    string num = to_string(id);
    s += num;
    s += ".txt";

    cerr<<"Processing :: "<<s<<endl;
    infile.open(s);
    int graph[185][185];
    memset(graph,0,sizeof graph);
    while(!infile.eof()){
        int u,v;
        string st;
        getline(infile, st);
        sscanf(st.c_str(), "%d %d", &u,&v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    infile.close();
    process(graph);
}


void generateTuples(){
    int n = 180;
    int ind = 0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            for(int k=j+1;k<=n;k++)
                mp[ Tuple(i,j,k) ] = ind++;
    int sz = (int)mp.size();
    occurs.resize(sz+10,0);
}

void print(){
    ofstream outfile;
    outfile.open("Occurrence.txt");
    for(auto x:mp){
        Tuple t = x.first;
        int id = x.second;
        int val = occurs[id];
        outfile<<id<<" "<<t.u<<","<<t.v<<","<<t.w<<" "<<val<<"\n";
    }
    outfile.close();
}
int main(){

    generateTuples();
    cerr<<(int)mp.size()<<endl;
    for(int i=0;i<300;i++)readFile(i);
    print();


    return 0;
}