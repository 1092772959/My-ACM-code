#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 1300;
int N;
struct Edge{
    LL val;
    int to,next;
}edges[maxn<<2];
int head[maxn],tot;
int linker[maxn];
bool used[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v, LL val)
{
    edges[tot].val = val;
    edges[tot].to = v;
    edges[tot].next = head[u];
    head[u] = tot++;
}

bool dfs(int u){
    int v;
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
    for(u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

int idx[60][60],idy[60][60];
char G[maxn][maxn];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int M;
    while(scanf("%d%d",&N,&M)==2){
        init();
        for(int i=1;i<=N;++i){
            scanf("%s",G[i]+1);
        }
        memset(idx,0,sizeof(idx));
        memset(idy,0,sizeof(idy));
        int cnt1=0,cnt2 = 0;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                if(G[i][j]!='*') continue;
                if(idx[i][j-1]) idx[i][j] = idx[i][j-1];
                else idx[i][j] = ++cnt1;
                if(idy[i-1][j]) idy[i][j] = idy[i-1][j];
                else idy[i][j] = ++cnt2;
            }
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                if(G[i][j]=='*')
                    AddEdge(idx[i][j],idy[i][j],0);
            }
        }
        N = cnt1;
        printf("%d\n",hungary());
    }
    return 0;
}