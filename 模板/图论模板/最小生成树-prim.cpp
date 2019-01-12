#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
const double INF =1e30;
struct Node{
    int x,y;
}p[maxn];

int N;
double d[maxn];
double G[maxn][maxn];
bool vis[maxn];

int prim(){
    int MST =0;
    memset(vis,0,sizeof(vis));
    vis[1] = true;
    for(int i=1;i<=N;++i) d[i] =G[1][i];
    for(int i=1;i<N;++i){
        int min = INF;
        int u;
        for(int j=1;j<=N;++j){
            if(!vis[j] && min>d[j]){
                u =j;
                min = d[j];    
            }
        }
        if(min==INF) return -1;            
        MST+=min;
        vis[u] = true;
        for(int j =1;j<=N;++j){
            if(!vis[j] && d[j]>G[u][j]){
                d[j] = G[u][j];
            }
        }
    }
    return MST;
}
