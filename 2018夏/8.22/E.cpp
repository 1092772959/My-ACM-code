#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e5+5;
struct node{
	int v,next;
}edges[N<<1];
int head[N],e;
int id[N]; 
int RMQ[N*3][20];
int curID;
int F[N*3],B[N*3];
int n,m,Q,root;
int val[N];
int res[N];
vector<int> num[N];
int mx;

void init(){
    e = 0; curID = 0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<N;++i) num[i].clear();
}

void Add (int u,int v)
{
	edges[e].v=v;
	edges[e].next=head[u];
	head[u]=e++;
}
 
void DFS (int u,int p,int Dep)
{
	int i,v;
	curID++;
	F[curID]=u;
	B[curID]=Dep;
	id[u]=curID;
	for (i=head[u];i!=-1;i=edges[i].next){
		v=edges[i].v;
		if (v==p) continue;
		DFS(v,u,Dep+1);
		curID++;
		F[curID]=u;
		B[curID]=Dep;
	}
}

void initRMQ()
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
	if (a>b) k=a,a=b,b=k;
    k = 31 - __builtin_clz(b - a + 1);
	x=RMQ[a][k];
	y=RMQ[b-(1<<k)+1][k];  
	return B[x]<B[y]?F[x]:F[y];
}
 
void gao(int w)
{
    vector<int> p;
    for(int i=w;i<=mx;i+=w){
        for(auto &v:num[i]){
            p.push_back(v);
        }
    }
    sort(p.begin(),p.end(),[&](int x,int y){return id[x]<id[y];});
    int len = p.size();
    for(int i=1;i<len;++i){
        int lca=  getLCA(p[i],p[i-1]);
        res[lca] = max(res[lca],w);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
	int N;
    while(~scanf("%d",&N)){
        init();
        memset(res,-1,sizeof(res));
        int u,v,tmp;
        for(int i=2;i<=N;++i){
            scanf("%d",&u);
            Add(u,i);
            Add(i,u);
        }
        DFS(1,-1,1);
        initRMQ();
        mx = -1;
        for(int i=1;i<=N;++i){
            scanf("%d",&val[i]);
            mx = val[i]>mx? val[i] : mx;  
            num[val[i]].push_back(i);
        }
        for(int i=mx;i>=1;--i)
            gao(i);
        for(int i=1;i<=N;++i)
            printf("%d\n",res[i]);
    }
    return 0;
}
