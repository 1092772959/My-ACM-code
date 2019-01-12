#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>#
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn =2e2+5;
const int maxM = 1<<20;
#define INF 0x3f3f3f3f

struct Node{
    int x,y;
}point[maxn];

double G[maxn][maxn];
double d[maxn];
bool vis[maxn];

inline double dist(Node & a,Node &b)    {return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

void dij(int s,int n) {
    memset(vis,0,sizeof(vis));
	for (int i = 1; i <= n; i++)
		d[i] = G[1][i];
	d[s] = 0;
    vis[s]= true;
	for (int i = 1; i <= n; i++){
		int p = -1;
		double minn = INF;
		for (int j = 1; j <= n; j++){
			if (!vis[j] && d[j] < minn){
				minn = d[j];
				p = j;
			}
		}
		if (p == -1) break;
		vis[p] = true;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && max(G[p][j],d[p]) < d[j]){       //寻求更小的路
				d[j] = max(G[p][j],d[p]);
			}
		}
	}
}

int main()
{
    int T=1, N,u,v,x,y,tmp;
    while(scanf("%d",&N)==1,N){
        for(int i =1;i<=N;++i){
            scanf("%d%d",&point[i].x,&point[i].y);
        }
        for(int i=1;i<=N;++i){
            G[i][i]=0;
            for(int j=i+1;j<=N;++j){
                G[i][j] = G[j][i] = dist(point[i],point[j]);
            }
        }
        dij(1,N);
        printf("Scenario #%d\n",T++);
        printf("Frog Distance = %.3f\n",d[2]);
        printf("\n");
    }
    return 0;
}


