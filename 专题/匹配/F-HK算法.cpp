#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
const int MAXN = 3010;
const int MAXM = 3010*3010;
const int INF = 0x3f3f3f3f;

int N;
struct Node{
    int x,y;
}p[MAXN],it[MAXN];
int v[MAXN];

struct Edge{
	int v;
	int next;
}edge[MAXM];
 
int nx, ny;
int cnt;
int t;
int dis;
 
int first[MAXN];
int xlink[MAXN], ylink[MAXN]; 
/*xlink[i]表示左集合顶点所匹配的右集合顶点序号，ylink[i]表示右集合i顶点匹配到的左集合顶点序号。*/
int dx[MAXN], dy[MAXN]; 
/*dx[i]表示左集合i顶点的距离编号，dy[i]表示右集合i顶点的距离编号*/
int vis[MAXN]; //寻找增广路的标记数组 
 
void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(xlink, -1, sizeof(xlink));
	memset(ylink, -1, sizeof(ylink));
}
 
void AddEdge(int u, int v)
{
	edge[cnt].v = v;
	edge[cnt].next = first[u], first[u] = cnt++;
}
 
int bfs()
{
	queue<int> q;
	dis = INF;
	memset(dx, -1, sizeof(dx));
	memset(dy, -1, sizeof(dy));
	for(int i = 1; i <= nx; i++){
		if(xlink[i] == -1){
			q.push(i);
			dx[i] = 0;
		}
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(dx[u] > dis) break;
		for(int e = first[u]; e != -1; e = edge[e].next){
			int v = edge[e].v;
			if(dy[v] == -1){
				dy[v] = dx[u] + 1;
				if(ylink[v] == -1) dis = dy[v];
				else{
					dx[ylink[v]] = dy[v]+1;
					q.push(ylink[v]);
				}
			}
		}
	}
	return dis != INF;
}
 
int find(int u)
{
	for(int e = first[u]; e != -1; e = edge[e].next){
		int v = edge[e].v;
		if(!vis[v] && dy[v] == dx[u]+1){
			vis[v] = 1;
			if(ylink[v] != -1 && dy[v] == dis) continue;
			if(ylink[v] == -1 || find(ylink[v])){
				xlink[u] = v, ylink[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
 
int MaxMatch()
{
	int ans = 0;
	while(bfs()){
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= nx; i++) 
            if(xlink[i] == -1)  
                ans += find(i);
	}
	return ans;
}

double dist(Node &a,Node &b)
{
    double dx = a.x-b.x,dy = a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}


#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,tmp,K,cas=1;
    double t;
    scanf("%d",&T);
    while(T--){
        scanf("%lf%d",&t,&nx);
        init();
        for(int i=1;i<=nx;++i) scanf("%d%d%d",&p[i].x,&p[i].y,&v[i]);
        scanf("%d",&ny);
        for(int i=1;i<=ny;++i) {
            scanf("%d%d",&it[i].x,&it[i].y);
            for(int j=1;j<=nx;++j){
                double d = dist(p[j],it[i]);
                if(d/v[j]*1.0<=t) 
                    AddEdge(i,j);
            }
        }
        printf("Scenario #%d:\n", cas++);
        printf("%d\n\n",MaxMatch());
    }
    return 0;
}
