#include<bits/stdc++.h>
using namespace std;
const int maxn =105;
const int INF = 0x3f3f3f3f;
int G[maxn][maxn],path[maxn][maxn];
int dist[maxn],pre[maxn];
bool used[maxn][maxn],vis[maxn];

void init(int N){
    for(int i=0;i<=N;++i){
        for(int j=i;j<=N;++j){
            G[i][j]=G[j][i]=INF;
        }
    }
}
void AddEdge(int u,int v,int val)   {G[v][u]=G[u][v]=val;}


int Prim(int N){
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
            if(vis[j] && j!=u){     //更新点对得path
                path[u][j]=path[j][u]=max(path[j][pre[u]],dist[u]); ////////////////////?????????
            }
            else if(!vis[j]){       //更新dist
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
        }
        int Mst = Prim(N);
        int res=INF;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(!used[i][j] && i!=j){
                    res = min(res,Mst+G[i][j]-path[i][j]);
                }
            }
        }
        printf("%d %d\n",Mst,res);
    }
    return 0;
}