#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5,maxm = 2e6+5;
int N,M;
struct Node{
    int K[15];
}link[maxn];
int cnt[15];
struct Edge{
    int to,next;
}edges[maxm];
int head[maxn],tot;
bool used[15];
int limit[15];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
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
            if(cnt[v]<limit[v]){
                link[v].K[cnt[v]++]=u;
                return true;
            }
            for(int j=0;j<cnt[v];++j){
                if(dfs(link[v].K[j])){
                    link[v].K[j]=u;
                    return true;
                }
            }
        }
    }
    return false;
}

bool hungary(){
    memset(cnt,0,sizeof(cnt));
    for(int u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(!dfs(u)) return false;     //只要有一个人不能匹配则失败
    }
    return true; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,u,v,tmp,k;
    int op;
    while(scanf("%d%d",&N,&M)==2){
        init();
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                scanf("%d",&op);
                if(op) AddEdge(i,j);    
            }
        }
        for(int i=1;i<=M;++i) scanf("%d",&limit[i]);
        if(hungary()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

