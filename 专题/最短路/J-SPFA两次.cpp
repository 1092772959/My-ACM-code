#include<iostream>
#include<cstring>
#include<stdio.h>
#include<map>
#include<string>
#include<algorithm>
#include<queue>
//#define LOCAL
using namespace std;
typedef long long LL;
const LL INF =(1ll<<60);
const int maxn =1e6+5;

struct Edge{
    int to,next;
    LL val;
};

struct SPFA{
    int head[maxn];
    Edge edges[maxn];
    LL d[maxn];
    bool inq[maxn];
    int n,tot;
    
    void init(int n){
        this->tot=0;
        this->n = n;
        memset(head,-1,sizeof(head));
    }
    void AddEdge(int u,int v,LL val){
        edges[tot].to = v;
        edges[tot].val = val;
        edges[tot].next = head[u];
        head[u] = tot++;
    }

    void spfa(int s){
        for(int i=0;i<=n;++i){
            inq[i]=false;
            d[i] = INF;
        }
        queue<int> Q;
        Q.push(s);
        d[s]=0; inq[s] = true;
        while(!Q.empty()){
            int x = Q.front();Q.pop();
            inq[x] =false;
            for(int i = head[x];~i;i=edges[i].next){
                int v = edges[i].to;
                if(d[v]>d[x]+edges[i].val){
                    d[v] = d[x]+edges[i].val;
                    if(!inq[v]){
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
    }
}G,rG;

int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,u,v;
    LL tmp;
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        G.init(N);
        rG.init(N);
        for(int i=1;i<=M;++i){
            scanf("%d%d%lld",&u,&v,&tmp);
            G.AddEdge(u,v,tmp);
            rG.AddEdge(v,u,tmp);
        }
        G.spfa(1);
        rG.spfa(1);
        LL res=0;
        for(int i=2;i<=N;++i){
            res+=G.d[i]+rG.d[i];
        }
        printf("%lld\n",res);
    }
    return 0;
}