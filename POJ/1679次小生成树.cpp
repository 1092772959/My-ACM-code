#include<iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn =1e2+5;
const int INF = 0x3f3f3f3f;
int G[maxn][maxn],dist[maxn];
int path[maxn][maxn];       //记录生成树上每对结点得最大边权
bool used[maxn][maxn];
int pre[maxn];
bool vis[maxn];
struct Edge{
    int to,val;
};

void init(int N)
{
    for(int i=0;i<=N;++i){
        for(int j=i;j<=N;++j){
            G[i][j]=G[j][i]=INF;
        }
    }
}

void AddEdge(int u,int v,int val)
{
    G[v][u]=G[u][v]=val;
}


int prim(int N)
{
    int Mst=0;
    memset(used,0,sizeof(used));
    memset(path,0,sizeof(path));
    memset(vis,0,sizeof(vis));
    vis[1]=true;                    //从1开始
    
    for(int i=1; i<=N; ++i){
        dist[i]=G[1][i];
        pre[i]=1;
    }

    for(int i=1;i<N;++i){
        int u=-1;
        for(int j=1;j<=N;++j){
            if(!vis[j] && (u==-1 || dist[j]<dist[u]))
                u=j;
        }        
        used[u][pre[u]]= used[pre[u]][u]=true;
        vis[u]=true;
        Mst+=G[pre[u]][u];
        for(int j=1;j<=N;++j){
            if(vis[j] && j!=u){     //若j已经被访问且不是u本身，更新点对u和j的path
                path[u][j]=path[j][u]=max(path[j][pre[u]],dist[u]); 
            }
            else if(!vis[j]){       //若j没被访问，更新dist
                if(dist[j]>G[u][j]){
                    dist[j]=G[u][j];
                    pre[j]=u;
                }
            }
        }
    }
    return Mst;
}

int main()
{
    int T,N,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            AddEdge(u,v,tmp);
            AddEdge(v,u,tmp);
        }
        int Mst=prim(N);
        int res=INF;
        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                if(i!=j && !used[i][j]){
                    res=min(res,Mst+G[i][j]-path[i][j]);        //检查每对结点
                }
            }
        }

        if(res==Mst)printf("Not Unique!\n");
        else    printf("%d\n",Mst);
    }
    return 0;
}