#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn =300,maxm = 1e5+5;
const int INF = 0x3f3f3f3f;
struct Node{
    int K[20];
}link[50];
int cnt[50];
struct Edge{
    int to,next;
}edges[maxm];
int head[maxn],tot;
bool used[50];

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

bool dfs(int u,int limit){
    int v;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v]){
            used[v]=true;
            if(cnt[v]<limit){
                link[v].K[cnt[v]++]=u;
                return true;
            }
            for(int j=0;j<cnt[v];++j){
                if(dfs(link[v].K[j],limit)){
                    link[v].K[j]=u;
                    return true;
                }
            }
        }
    }
    return false;
}

bool hungary(int Nx,int limit){
    memset(cnt,0,sizeof(cnt));
    for(int u=1;u<=Nx;u++){
        memset(used,0,sizeof(used));
        if(!dfs(u,limit)) return false;     //只要有一个人不能匹配则失败
    }
    return true; 
}

int G[maxn][maxn];
int Floyd(int N)
{
    int mx=0;
    for(int k=1;k<=N;++k){
        for(int i=1;i<=N;++i){
            if(G[i][k]==INF) continue;    
            for(int j=1;j<=N;++j){
                if(G[k][j]==INF)  continue; 
                G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
                mx= max(G[i][j],mx);
            }
        }
    }
    return mx;
}

bool OK(int K,int C,int M,int limit)
{
    init();
    for(int i=1;i<=C;++i){
        for(int j=1;j<=K;++j){
            if(G[K+i][j]<=limit) AddEdge(i,j);
        }
    }
    if(hungary(C,M)) return true;
    else return false; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int S,T,K,C,N,M,u,v,tmp;
    while(scanf("%d%d%d",&K,&N,&M)==3){
        int sc = K+N;
        memset(G,0,sizeof(G));
        for(int i=1;i<=sc;++i)
            for(int j=1;j<=sc;++j){
                scanf("%d",&G[i][j]);
                if(!G[i][j]) G[i][j] = INF;
            }
        int L=0,R=200*(K+N),ans=Floyd(sc);
        while(L<=R){                         //最大值最小化
            int mid =(L+R)>>1;
            if(OK(K,N,M,mid)){
                ans = mid;
                R=mid-1;
            }
            else L = mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
