#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int first[maxn], head[maxn], cnt, sum;
struct edge{
	int u, v, w, next;
}e[maxn*2], qe[maxn<<1], Q[maxn];
int ans[maxn];                  //祖先
int f[maxn], vis[maxn];
int d[maxn],d2[maxn];

void AddEdge(int u, int v, int w)
{
	e[cnt].u = u;
	e[cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = first[u];
	first[u] = cnt++;
}
 
void AddEdge2(int u, int v, int w)
{
	qe[sum].u = u;
	qe[sum].v = v;
	qe[sum].w = w;
	qe[sum].next = head[u];
	head[u] = sum++;
}
 
int find(int x)
{
    return f[x]==x? f[x]:f[x] = find(f[x]);
}

void LCA(int u)
{
	f[u] = u;
	vis[u] = true;
	for(int i = first[u]; i != -1; i = e[i].next){
		int v = e[i].v;
		if(vis[v])
			continue;	
        d[v] = d[u] +e[i^1].w;
        d2[v] = d2[u]+e[i].w;
		LCA(v);
		f[v] = u;
	}
	for(int i = head[u]; i != -1; i = qe[i].next){
		int v = qe[i].v;
		if(vis[v])
			ans[qe[i].w] = find(v);
	}
} 

int main()
{
	int T,n, m;
	scanf("%d",&T);
	while(T--){
		memset(first, -1, sizeof(first));
		memset(head, -1, sizeof(head));
		cnt = 0;
		sum = 0;
		scanf("%d", &n);
		int tot=0;
		for(int i = 0; i < n-1; i++){
			int u, v, c1,c2;
			scanf("%d %d %d %d", &u, &v, &c1,&c2);
			if(u>v){
				swap(u,v);
				swap(c1,c2);
			}
			AddEdge(u, v, c1);
			AddEdge(v, u, c2);
			tot+=c1+c2;
		}
		int q;
		scanf("%d", &q);
		for(int i = 0; i < q; i++){
			int u, v; 
			scanf("%d %d", &u, &v);
			Q[i].u = u, Q[i].v = v;
			AddEdge2(u, v, i);
			AddEdge2(v, u, i);
		}
		memset(vis, 0, sizeof(vis));
		d[1] = 0;d2[1]=0;
		LCA(1);
		for(int i = 0; i < q; i++){
			int u = Q[i].u, v = Q[i].v;
			int tmp = ans[i];
            printf("%d\n", tot-(d[v]+d2[u]-d[tmp]-d2[tmp]));
		}
	}
	return 0;
}