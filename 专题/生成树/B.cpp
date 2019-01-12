#include<iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn =1e3+5;
const int INF = 0x3f3f3f3f;
struct Point{
    int x,y;
    int population;
}P[maxn];
double G[maxn][maxn];
double dist[maxn];
double path[maxn][maxn];       //记录生成树上每对结点得最大边权
bool used[maxn][maxn];
int pre[maxn];
bool vis[maxn];

inline double distance(int i,int j)
{
    return sqrt((double)(P[i].x-P[j].x)*(P[i].x-P[j].x)+(double)(P[i].y-P[j].y)*(P[i].y-P[j].y));
}

double prim(int N)
{
    double Mst=0;
    memset(used,0,sizeof(used));
    memset(path,0,sizeof(path));
    memset(vis,0,sizeof(vis));
    vis[1]=true;                    //从1开始
    
    for(int i=2; i<=N; ++i){
        dist[i]=G[1][i];
        pre[i]=1;
    }

    for(int i=1;i<N;++i){
        int u=-1;
        for(int j=1;j<=N;++j){
            if(!vis[j] && (u==-1 || dist[j]<dist[u]))
                u=j;
        }        
        used[u][pre[u]] = used[pre[u]][u] = true;
        vis[u]=true;
        Mst+=G[pre[u]][u];
        for(int j=1;j<=N;++j){
            if(vis[j] && j!=u){     //更新点对得path
                path[u][j] = path[j][u] = max(path[pre[u]][j],dist[u]);
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
    double d;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i=1;i<=N;++i){
            scanf("%d%d%d",&P[i].x,&P[i].y,&P[i].population);
        }
        for(int i=1;i<=N;++i){
            for(int j=i+1;j<=N;++j){
                if(i==j) G[i][j]=0;
                G[i][j]=G[i][j]=distance(i,j);
            }
        }
        double Mst=prim(N);
        double res=-1;

        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                if(i==j) continue;
                if(used[i][j])
                    res = max(res,(P[i].population+P[j].population)/Mst-G[i][j]);
                else
                    res = max(res,(P[i].population+P[j].population)/(Mst-path[i][j]));
            }
        }

        printf("%.2f\n",res);        
    }
    return 0;
}
