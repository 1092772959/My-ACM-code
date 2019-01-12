#include<iostream>
#include<cstring>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef long long LL;
const int MAXN = 1e3+5;
const int MAXM = 4e4+5;
const int INF = 0x3f3f3f3f;
queue<int>q;
int N,M;
struct Edge{
    int v,next;
    int w;
};

struct Spfa{
    int N,M;
    bool inq[MAXN];
    int dp[MAXN],cnt[MAXN];
    int pre[MAXN];
    int head[MAXN],tot;
    int dis[MAXN];
    Edge edge[MAXM];

    void init(int n){
        N = n;
        tot = 0;
        memset(head,-1,sizeof(head));
        memset(cnt,0,sizeof(cnt));
    }

    void Addedge(int u,int v,int w){
        edge[tot].v = v;
        edge[tot].w = w;
        edge[tot].next = head[u];
        head[u] = tot++;
    }

    bool spfa(int s){
        memset(inq,false,sizeof(inq));
        for (int i = 1 ; i <= N ; i++) dis[i] = INF;
        while (!q.empty()) q.pop();
        q.push(s);
        dis[s] = 0;
        cnt[s] = 1;
        inq[s] = true;
        while (!q.empty()){
            int u = q.front(); q.pop();
            inq[u] = false;
            for (int i = head[u] ; i != -1 ; i = edge[i].next){
                int v = edge[i].v;
                if (dis[v] > dis[u] + edge[i].w){
                    dis[v] = dis[u] + edge[i].w;
                    if (!inq[v]){
                        inq[v] = true;
                        cnt[v]++;
                        q.push(v);
                        if (cnt[v] >= N) return false;
                    }
                }
            }
        }
        return true;
    }
}G;


#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,ML,MD,T,u,v,cas=1;
    int tmp;
    while(scanf("%d%d%d",&N,&ML,&MD)==3){
        G.init(N);
        for(int i=1;i<=ML;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            if(u>v) swap(u,v);
            G.Addedge(u,v,tmp);
        }
        for(int i=1;i<=MD;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            if(u<v) swap(u,v);
            G.Addedge(u,v,-tmp);
        }
        if(!G.spfa(1)) puts("-1");
        else if(G.dis[N]==INF) puts("-2");
        else printf("%d\n",G.dis[N]);
    }
    return 0;
}
