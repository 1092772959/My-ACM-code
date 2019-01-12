#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
const int maxn = 6e2+5;
const int maxm = maxn*maxn;
int N;
struct Edge{
    int to,next;
}edges[maxm];
int head[maxn],tot;
int linker[maxn];
bool used[maxn];
int cnt;

void init(){
    tot=0;
    cnt=1;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edges[tot].to = v;
    edges[tot].next = head[u];
    head[u] = tot++;
}

bool dfs(int u){
    int v,st,ed;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v]){
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v])){
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int u;
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(u=1;u<=cnt;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

char op[maxn];
int G[maxn][maxn];
int d[4][2] = {1,0,-1,0,0,1,0,-1};


void debug(){
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j) cout<<G[i][j]<<" ";
        cout<<endl;
    }
}

bool check(int x,int y)
{
    if(x<1 || x>N || y<1 || y>N) return false;
    if(!G[x][y]) return false;
    return true;
}

#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,tmp,K,cas=1;
    double t;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&N);
        for(int i=1;i<=N;++i){
            scanf("%s",op);
            for(int j=1;j<=N;++j){
                if(op[j-1]=='#')    G[i][j]=++cnt;
                else G[i][j]=0;
            }
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                int u =G[i][j];
                if(!u) continue;
                for(int k=0;k<4;++k){
                    int nx = i+d[k][0],ny = j+d[k][1];
                    if(!check(nx,ny)) continue;
                    int v =G[nx][ny];
                    AddEdge(u,v);
                }
            }
        }
        //debug();
        printf("Case %d: %d\n",cas++,hungary()/2);
    }
    return 0;
}
