#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const  int maxn=2e3+5;
const int INF=1<<29;
typedef struct node{
	int p,w;
	node(int a,int b){p=a;w=b;}
	friend bool operator<(node a,node b){
	    if(a.w!=b.w) return a.w>b.w;
	    return a.p>b.p;
	}
};
vector <node> eg[maxn];
int dis[maxn],n;

void Dijkstra(int src)
{
	for(int i=0;i<=n;i++) dis[i]=INF;
	dis[src]=0;
	priority_queue <node> Q;
	Q.push(node(src,dis[src]));
	while(!Q.empty()){
		node f=Q.top();Q.pop();
		for(int i=0;i<eg[f.p].size();i++){
			node t=eg[f.p][i];
			if(dis[t.p]>t.w+f.w){ //三角形原则更新距离
				dis[t.p]=t.w+f.w;
				Q.push(node(t.p,dis[t.p]));
			}
		}
	}
 
}
int main()
{
	int u,v,m,w;
	while(scanf("%d%d",&m,&n)!=EOF){
		for(int i=0;i<=n;i++) eg[i].clear();
		while(m--){
			scanf("%d%d%d",&u,&v,&w);
			eg[u].push_back(node(v,w));
			eg[v].push_back(node(u,w));
		}
		Dijkstra(1);
		printf("%d\n",dis[n]);
	}
	return 0;
}