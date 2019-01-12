#include<iostream>
#include<string>
#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1010;
struct point{
    int x,y;
}p[N];

double G[N][N],dist[N];
double path[N][N];
int population[N];
int pre[N],visit[N];
bool used[N][N];
int n;
 
inline double Dist(point v1,point v2){
    return sqrt(double(v1.x-v2.x)*(v1.x-v2.x)+double(v1.y-v2.y)*(v1.y-v2.y));
}
 
double Prim()
{
    double Mst=0;
    memset(visit, 0, sizeof(visit));
    memset(used, 0, sizeof(used));
    memset(path, 0, sizeof(path));
    visit[1]=1;
    for(int i=1; i<=n; ++i){
        dist[i] = G[1][i];
        pre[i] = 1;
    }
    for(int i=1; i<n; ++i){
        int u=-1;
        for(int j=1; j<=n; ++j){
            if(!visit[j]){
                if(u==-1||dist[j]<dist[u])
                    u=j;
            }
        }
        used[u][pre[u]]=used[pre[u]][u] = true;
        Mst+=G[pre[u]][u];
        visit[u]=1;
        for(int j=1; j<=n; ++j){
            if(visit[j]&&j!=u){
                path[u][j]=path[j][u]=max(path[j][pre[u]], dist[u]);
            }
            if(!visit[j]){
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
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        memset(G,0,sizeof(G));
        for(int i=1; i<=n; ++i)
            scanf("%d%d%d",&p[i].x,&p[i].y,&population[i]);
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if(i!=j)
                    G[i][j]=Dist(p[i],p[j]);
            }
        }
        double Mst=Prim();
        double res=-1;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j)
                if(i!=j){
                    if(used[i][j])
                        res=max(res,(population[i]+population[j])/(Mst-G[i][j]));
                    else
                        res=max(res,(population[i]+population[j])/(Mst-path[i][j]));
                }
        }
        printf("%.2f\n",res);
    }
    return 0;
}
