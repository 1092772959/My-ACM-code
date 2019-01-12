#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 3010;
const int MAXM = 3010*3010;
const int INF = 0x3f3f3f3f;
int N;
struct Node{
    int x,y;
}p[MAXN],it[MAXN];

struct Edge{
	int v,next;
}edge[MAXM];
int nx, ny;
int cnt;
int t;	
int dis;

int head[MAXN];
int xlink[MAXN], ylink[MAXN]; 
/*xlink[i]表示左集合顶点所匹配的右集合顶点序号，
ylink[i]表示右集合i顶点匹配到的左集合顶点序号。*/
int dx[MAXN], dy[MAXN]; 
/*dx[i]表示左集合i顶点的距离编号，dy[i]表示右集合i顶点的距离编号*/
int vis[MAXN]; //寻找增广路的标记数组 

void init(){
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(xlink, -1, sizeof(xlink));
	memset(ylink, -1, sizeof(ylink));
}
 
void AddEdge(int u, int v)
{
	edge[cnt] = (Edge){v,head[u]};
	head[u] = cnt++;
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
		for(int e = head[u]; e != -1; e = edge[e].next){
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
	for(int e = head[u]; e != -1; e = edge[e].next){
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
