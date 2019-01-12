#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const int maxn=100005;
struct node{
	int v,next;
    LL dis;
}edges[maxn<<1];
int head[maxn],e;
int id[maxn]; //节点第一次被遍历的顺序
LL dis[maxn]; //节点到根节点的距离
int RMQ[maxn*3][20];
int curID;
//F[i]表示第i个遍历的节点
//B[i]表示F[i]在树中的深度
int F[maxn*3],B[maxn*3];
int n,m,Q,root;

void init()
{
    e = 0;
    curID = 0;
    memset(head,-1,sizeof(head));
}

void AddEdge (int u,int v,LL dis)
{
	edges[e].v=v;
	edges[e].dis=dis;
	edges[e].next=head[u];
	head[u]=e++;
}
 
void DFS (int u,int p,int Dep,LL d)
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

LL dist(int u,int v)
{
    return dis[u]+dis[v] -2*dis[getLCA(u,v)];
}

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int T,N,Q,u,v;
    LL w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&Q);
        init();
        for(int i=1;i<=N-1;++i){
            scanf("%d%d%lld",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        int X,Y; LL Z;
        scanf("%d%d%lld",&X,&Y,&Z);
        DFS(1,-1,0,0);
        initRMQ();
        while(Q--){
            scanf("%d%d",&u,&v);
            LL ans = dist(u,v);
            ans=min(ans,dist(u,X)+dist(v,X));
            ans=min(ans,dist(u,Y)+dist(v,Y));
            ans=min(ans,dist(u,X)+dist(v,Y)+Z);
            ans=min(ans,dist(u,Y)+dist(v,X)+Z);
            printf("%lld\n",ans);
        }
    }
    return 0;
}