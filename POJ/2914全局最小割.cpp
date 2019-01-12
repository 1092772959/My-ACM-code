#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

const int maxn =510;
const int INF =0x3f3f3f3f;
struct stoer_wagner{
	int n;					//点数
	int mp[maxn][maxn];		//邻接表存储边的权值
    int node[maxn],dis[maxn];
	void Init(int n){
		this->n=n;
		memset(mp,0,sizeof mp);
	}
	void addEdge(int u,int v,int cost){	
		mp[u][v]+=cost;
		mp[v][u]+=cost;
	}
    int Sw(){
        int i,j,now,ans=0x3fffffff;
        for(int i=0;i<n;++i) node[i]=i;
        while(n>1){
            for(now=0,i=1;i<n;++i) dis[node[i]]=0;
            for(int i=1;i<n;++i){
                swap(node[now],node[i-1]);
                for(now=j=i;j<n;++j){
                    dis[node[j]]+=mp[node[i-1]][node[j]];
                    if(dis[node[now]]<dis[node[j]]) now=j;
                }
            }
            ans = min(ans,dis[node[now]]);
            for(j=0;j<n;++j) mp[node[j]][node[now-1]] = mp[node[now-1]][node[j]]+=mp[node[j]][node[now]];
            node[now] = node[--n];
        }
        return ans;
    }
}G;	

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        G.Init(N);
        for(int i=1;i<=M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            G.addEdge(u,v,tmp);
        }
        printf("%d\n",G.Sw());
    }
    return 0;
}
