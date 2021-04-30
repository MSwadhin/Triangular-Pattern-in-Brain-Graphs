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

typedef pair<int,int> pii;
vector<pii> foundInTestGraph;// first->tuples, second->pairs

void process(int graph[185][185]){ // Given Adjacency Matrix
    int n = 180;
    int pairs = 0;
    int tuples = 0;
    for(Tuple t:TestTuples ){
        if( graph[t.u][t.v] && graph[t.u][t.w] && graph[t.v][t.w])tuples++;
        vector<int> nodes;
        nodes.push_back(t.u);
        nodes.push_back(t.v);
        nodes.push_back(t.w);
        bool fnd = 0;
        do{
            int u = nodes[0],v = nodes[1], w = nodes[2];
            if( graph[u][v] && graph[v][w] ){
                fnd = 1;
                break;
            }
        }while(next_permutation(nodes.begin(),nodes.end()));
        if(fnd)pairs++;
    }
    foundInTestGraph.push_back(pii(tuples,pairs));
}



void readFile(int id){// Read Graph From ith File
    ifstream infile;
    string s = "graph_connectome_";
    string num = to_string(id);
    s += num;
    s += ".txt";

    cerr<<"Processing Test For :: "<<s<<endl;

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

void takeTestTuples(){
    ifstream infile;
    infile.open("OC100.txt");
    while(!infile.eof()){
        string s;
        getline(infile,s);
        int u,v,w;
        sscanf(s.c_str(),"%d %d %d",&u,&v,&w);
        TestTuples.push_back(Tuple(u,v,w));
    }
    infile.close();
}
void print(){
    ofstream outfile;
    outfile.open("R100.txt");
    for(int i=0;i<(int)foundInTestGraph.size();i++){
        int t = foundInTestGraph[i].first;
        int p = foundInTestGraph[i].second;
        int tot = p;
        double success = 100.*t / (tot);
        outfile<<i+1<<"\t"<<p<<"\t"<<t<<"\t"<<success<<"\n";
    }
    outfile.close();
}


int main(){


    takeTestTuples();
    cerr<<(int)TestTuples.size()<<endl;

    for(int i=300;i<400;i++){
        readFile(i);
    }


    print();

    return 0;
}