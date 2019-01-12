#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn =1e3+5;
int N,M,cnt;
struct Edge{
    int to,next;
}edges[maxn<<4];
int head[maxn],tot;
int linker[maxn];
bool used[maxn];

void init()
{
    tot=0;
    cnt=0;
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
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int u=1;u<=cnt;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

int G[maxn][maxn];
char op[maxn];
int dir[4][2] = {1,0,-1,0,0,1,0,-1};

bool check(int x,int y){
    if(x<1||x>N || y<1||y>M) return false;
    if(!G[x][y]) return false;
    return true;
}

void debug(){
    for(int i =1;i<=N;++i){
        for(int j=1;j<=M;++j){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i){
            scanf("%s",op);
            for(int j=1;j<=M;++j){
                if(op[j-1]=='*') G[i][j]=++cnt;
                else G[i][j] = 0;
            }
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                int u =  G[i][j];
                if(!u) continue;
                for(int k =0;k<4;++k){
                    int nx = i+dir[k][0],ny = j+dir[k][1];
                    if(check(nx,ny)){
                        int v =G[nx][ny];
                        AddEdge(u,v);
                    }   
                }
            }
        }
        int res = cnt-hungary()/2;
        printf("%d\n",res);
    }
    return 0;
}
