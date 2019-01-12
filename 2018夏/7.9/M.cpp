#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{
	int v,dis,next;
}edges[N<<1];

int head[N],e;
int id[N]; //节点第一次被遍历的顺序
int dis[N]; //节点到根节点的距离
int rdis[N];    //根节点到节点的距离
int RMQ[N*3][20];
int curID;
//F[i]表示第i个遍历的节点
//B[i]表示F[i]在树中的深度
int F[N*3],B[N*3];
int n,m,Q,root;
int sum;

void Add (int u,int v,int dis)
{
	edges[e].v=v;
	edges[e].dis=dis;
	edges[e].next=head[u];
	head[u]=e++;
}

void DFS (int u,int p,int Dep,int d,int d2)
{
	int i,v;
	curID++;
	F[curID]=u;
	B[curID]=Dep;
	id[u]=curID;
	dis[u]=d;
    rdis[u]=d2;
	for (i=head[u];i!=-1;i=edges[i].next){
		v=edges[i].v;
		if (v==p) continue;
		DFS(v,u,Dep+1,d+edges[i^1].dis,d2+edges[i].dis);
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
		for (i=1;i+(1<<j)-1<=curID;i++)
		{
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
    sum=0;
	int i,u,v,c1,c2;
	char s[5];
	curID=0;
	memset(head,-1,sizeof(head));
	e=0;
	for (i=0;i<n-1;i++){
		scanf("%d%d%d%d",&u,&v,&c1,&c2);
        if(v>u){
            swap(u,v);
            swap(c1,c2);
        }
		Add(u,v,c1);
		Add(v,u,c2);
        sum+=c1+c2;
	}
	root=1;
}

int main ()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
		Input();
		DFS(root,0,0,0,0);
		initRMQ();
		int q,i,u,v;
        scanf("%d",&q);
        for (i=1;i<=q;i++){
            scanf("%d%d",&u,&v);
            int tmp=getLCA(u,v);
            printf("%d\n",sum-(dis[v]+rdis[u]-dis[tmp]-rdis[tmp]));
        }
	}
	return 0;
}