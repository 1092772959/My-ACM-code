#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn =105;
const int INF =0x3f3f3f3f;

int N,x[maxn*maxn],y[maxn*maxn];
int G[maxn][maxn];
int linker[maxn];
bool used[maxn];

void init(){memset(G,0,sizeof(G));}

void AddEdge(int u,int v)   {G[u][v]=1;}

bool dfs(int u){
    for(int v=1;v<=N;++v){
        if(!G[u][v]) continue;
        if(!used[v]){
            used[v]=true;
            if(linker[v]==-1 || dfs(linker[v])){
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
    for(int u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

int L[maxn],R[maxn];

//#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,v,tmp,K,cas=1;
    while(scanf("%d",&N)==1){
        init();
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                scanf("%d",&G[i][j]);
            }
        }
        int ans = hungary();
        if(ans<N){
            printf("-1\n");
            continue;
        }
        int res=0;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(j==i) continue;
                if(linker[j]==i){
                    L[res] = i,R[res++]=j;
                    swap(linker[j],linker[i]);
                    break;
                }
            }
        }
        printf("%d\n",res);
        for(int i=0;i<res;++i)
            printf("C %d %d\n",L[i],R[i]);
    }
    return 0;
}