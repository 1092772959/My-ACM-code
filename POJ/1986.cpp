#include<iostream>
#include<cstring>
#include<algorithm>
#include<stdio.h>
#include<cmath>
using namespace std;
const int N=40005;
struct node{
	int v,dis,next;
}edges[N<<1];
int head[N],e;
int id[N];
int dis[N];
int RMQ[N*3][20];
int curID;
int F[N*3],B[N*3];
int n,m,Q,root;
void Add (int u,int v,int dis)
{
	edges[e].v=v;
	edges[e].dis=dis;
	edges[e].next=head[u];
	head[u]=e++;
}
 
void DFS (int u,int p,int Dep,int d)
{
	int i,v;
	curID++;
	F[curID]=u;
	B[curID]=Dep;
	id[u]=curID;
	dis[u]=d;
	for (i=head[u];i!=-1;i=edges[i].next){
		v=edges[i].v;
		if (v==p) continue;
		DFS(v,u,Dep+1,d+edges[i].dis);
		curID++;
		F[curID]=u;
		B[curID]=Dep;
	}
}
 
void initRMQ ()
{
	int i,j,x,y;
	for (i=1;i<=curID;i++)
		RMQ[i][0]=i;
	for (j=1;(1<<j)<=curID;j++)
		for (i=1;i+(1<<j)-1<=curID;i++){
			x=RMQ[i][j-1];
			y=RMQ[i+(1<<(j-1))][j-1];
			RMQ[i][j]=B[x]<B[y]?x:y;
		}
}
 
int getLCA (int a,int b)
{
	int k,x,y;
	a=id[a];b=id[b];
	if (a>b)
		k=a,a=b,b=k;
	k=log(1.0+b-a)/log(2.0);
	x=RMQ[a][k];
	y=RMQ[b-(1<<k)+1][k];  
	return B[x]<B[y]?F[x]:F[y];
}
 
void Input ()
{
	int i,u,v,dis;
	char s[5];
	curID=0;
	memset(head,-1,sizeof(head));
	e=0;
	for (i=1;i<=m;i++){
		scanf("%d%d%d%s",&u,&v,&dis,s);
		Add(u,v,dis);
		Add(v,u,dis);
	}
	root=1;
}
 
int main ()
{
	while (~scanf("%d%d",&n,&m)){
		Input();
		DFS(root,0,0,0);
		initRMQ();
		int q,i,u,v;
        scanf("%d",&q);
        for (i=1;i<=q;i++){
            scanf("%d%d",&u,&v);
            int tmp=getLCA(u,v);
            printf("%d\n",dis[u]+dis[v]-2*dis[tmp]);
        }
	}
	return 0;
}