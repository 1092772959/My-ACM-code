#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long LL;
const int maxn =1e3+5;

int G[maxn][maxn];
int d[maxn];
bool vis[maxn];

void dij(int s,int n) {
    memset(vis,0,sizeof(vis));
	for (int i = 1; i <= n; i++)
		d[i] = G[1][i];
	d[s] = INF;
    vis[s]= true;
	for (int i = 1; i <= n; i++) {
		int p = -1;
		int mx = -1;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && d[j] > mx) {
				mx = d[j];
				p = j;
			}
		}
		if (p == -1) break;
		vis[p] = true;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && min(G[p][j],d[p]) > d[j]) {		//寻求更大的路
				d[j] = min(G[p][j],d[p]);
			}
		}
	}
}


int main()
{
    int T,cas=1,N,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
		memset(G,-1,sizeof(G));
        for(int i=1;i<=M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
			G[u][v] = G[v][u]= tmp;
        }
		dij(1,N);
		printf("Scenario #%d:\n%d\n\n",cas++,d[N]);
    }
    return 0;
}


