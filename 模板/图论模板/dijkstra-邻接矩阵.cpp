#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int INF = 0x3f3f3f3f;
const int maxn = 105;
int N;
int G[maxn][maxn];
int d[maxn];
bool vis[maxn];
void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i){
        G[i][i] =INF;
        for(int j=i+1;j<=N;++j){
            G[i][j] = G[j][i] =INF;
        }
    }
}

void dijkstra(int s)
{
    for(int i=1;i<=N;++i) d[i]=G[s][i];
    d[s] = 0;
    vis[s] = true;
    while(true){
        int u=-1;
        for(int i=1;i<=N;++i){
            if(!vis[i] && (u==-1 || d[i]<d[u])){
                u = i;
            }
        }
        if(u==-1) break;
        vis[u]=true;
        for(int i=1;i<=N;++i){
            if(!vis[i] && d[i] > d[u]+G[u][i]){
                d[i] = d[u]+G[u][i];
            }
        }
    }
}