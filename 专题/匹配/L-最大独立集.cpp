#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
const int maxn = 5e2+5;
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
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int u=1;u<=N;u++){                    //总的点数是cnt!!!
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

string like[maxn],dis[maxn];

#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,A,B,u,tmp,K,cas=1;
    while(scanf("%d%d%d",&A,&B,&N)==3){
        init();
        for(int i=1;i<=N;++i){
            char op1[5],op2[5];
            scanf("%s %s",op1,op2);
            like[i]=op1;
            dis[i]=op2;
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(i==j) continue;
                if(like[i]==dis[j] || dis[i]==like[j])  AddEdge(i,j);
            }
        }
        printf("%d\n",N-hungary()/2);           //求最大独立集
    }
    return 0;
}
