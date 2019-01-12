
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int Max = 110000;
typedef struct Node{
	int v;
	int next;
}Line; 
Line Li[Max*4];
int Head[Max],top;
int dfn[Max],low[Max],vis[Max]; 
int pre[Max],fa[Max]; 
int num;
int n,m,Q;
void AddEdge(int u,int v)
{
	Li[top].v = v; Li[top].next = Head[u];
	Head[u] = top++;
}
 
int Find(int x)
{
	return pre[x]==-1?x:pre[x]=Find(pre[x]);
}
 
void Union(int x,int y)
{
	int Fx = Find(x);
	int Fy = Find(y);
	if(Fx!=Fy)
		pre[Fx]=Fy;
}
 
void dfs(int fat,int u,int dep)
{
	dfn[u]=low[u]=dep;
	fa[u]=fat;
	vis[u] = 1;
	for(int i=Head[u];i!=-1;i=Li[i].next)
	{
        int v = Li[i].v;
		if(v!=fat&&vis[v]==1)
			low[u] = min(low[u],dfn[v]);
		if(vis[v]==0){
			dfs(u,v,dep+1);
			low[u] = min(low[u],low[v]);
			if(low[v]<=dfn[u])
				Union(v,u);
			else
				num++;
		}
	}
	vis[u]=2;
}
 
void Judge(int u)
{
	int x=Find(u);
	int y=Find(fa[u]);
	if(x!=y){
		num--;
		pre[x]=y;
	}
}
 
void LCA(int u,int v)//找公共祖先
{
	while(dfn[u]>dfn[v]){
		Judge(u);
		u=fa[u];
	}
	while(dfn[v]>dfn[u])
	{
		Judge(v);
		v=fa[v];
	}
	while(u!=v){
		Judge(u);
		Judge(v);
		u = fa[u];
		v = fa[v];
	}
}
int main()
{
	int z=1;
	while(~scanf("%d %d",&n,&m)&&(n+m)){
		top = 0;
		memset(Head,-1,sizeof(Head));
		int u,v;
		for(int i=0;i<m;i++){
			scanf("%d %d",&u,&v);
			AddEdge(u,v);
			AddEdge(v,u);
		}
		num = 0 ;
		memset(vis,0,sizeof(vis));
		memset(pre,-1,sizeof(pre));
		dfs(0,1,1);
		scanf("%d",&Q);
		printf("Case %d:\n",z++);
	    while(Q--){
			scanf("%d %d",&u,&v);
			if(Find(u)!=Find(v))
				LCA(u,v);
			printf("%d\n",num);
		}
		printf("\n");
	}
	return 0;
}