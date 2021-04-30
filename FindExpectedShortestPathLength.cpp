#include<bits/stdc++.h>
using namespace std;




// path[i] -> number of shortest paths of length i among all the graphs
int paths[185];
int cnt; // -> number of shortest paths of length < infinity

void process(int graph[185][185]){ // Given Adjacency Matrix

    int n = 180;
    int Dist[185][185];
    const int inf = 1e8;
    memset(Dist,0,sizeof Dist);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)Dist[i][j] = 0;
            else{
                if( graph[i][j] )Dist[i][j] = 1;
                else Dist[i][j] = inf;
            }
        }
    }


    // Floyd Warshall Algorithm
    for(int k=1;k<=n;k++){// k->intermediate node
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(Dist[i][k]<inf && Dist[k][j]<inf){
                    if( Dist[i][j] > Dist[i][k]+Dist[k][j] ){
                        Dist[i][j] = Dist[i][k]+Dist[k][j];
                    }
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(Dist[i][j] < inf){
                cnt++;
                int d = Dist[i][j];
                paths[d]++;
            }
        }
    }

}


void calculate(){

    cerr<<cnt<<endl;
    double ep = 0;
    for(int i=1;i<=180;i++){
        ep+= 1.0*i*paths[i];
    }
    ep /= (1.0)*cnt;
    cerr<<ep<<endl;
}

void readFile(int id){// Read Graph From ith File
    ifstream infile;
    string s = "graph_connectome_";
    string num = to_string(id);
    s += num;
    s += ".txt";
    cerr<<s<<endl;
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


int main(){

    /*
    *
    * FOUND EXPECTED LENGTH OF SHORTEST PATH : 2.03293 (ALL GRAPHS)
    * AVG SP LENGTH FROM TRAIN DATA : 2.06317
    */
    for(int i=0;i<300;i++)readFile(i);
    calculate();

    return 0;
}