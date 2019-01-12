#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef int LL;
const int maxn =1e3+5,maxm = 2e4+5;
const LL INF =0x3f3f3f3f;
struct Edge{
    int to,next;
    LL val;
};
struct Node{
    int u,cost,val;     //所在点，当前花费，剩余油量
    bool operator <(const Node &p) const {return cost>p.cost;}//花费小的优先级高
};

int dp[maxn][105];
bool vis[maxn][105];
int w[maxn];

struct Dijstra{
    int n,m,tot;
    Edge edges[maxm];
    int head[maxn];

    void init(int n){
        this->n = n;
        this->tot=0;
        memset(head,-1,sizeof(head));
    }

    void Addedge(int u,int v ,LL dist){
        edges[tot].to = v;
        edges[tot].val = dist;
        edges[tot].next = head[u];
        head[u] = tot++;
    }
    
    void BFS(int cap,int s,int t){
        memset(vis,0,sizeof(vis));
        memset(dp,INF,sizeof(dp));
        dp[s][0]=0;
        priority_queue<Node> Q;
        Q.push((Node){s,0,0});
        while(!Q.empty()){
            Node x  =Q.top();Q.pop();
            int u =x.u, ct = x.cost,val = x.val;
            vis[u][val] = true;
            if(u==t){                               //finish
                printf("%d\n",ct);
                return;
            }
            if(val<cap && !vis[u][val+1] && dp[u][val]+w[u]<dp[u][val+1]){        //需要加油
                dp[u][val+1] = dp[u][val] +w[u];
                Q.push((Node){u,dp[u][val+1],val+1});
            }
            for(int i=head[u];~i;i=edges[i].next){                          //遍历邻接点
                int  w =edges[i].val, v = edges[i].to;
                if(val>=w  && !vis[v][val-w] && ct < dp[v][val-w]){
                    dp[v][val-w] =ct;
                    Q.push((Node){v,ct,val-w});
                }
            }      
        }
        printf("impossible\n");
    }
}G;

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v;
    int tmp;
        scanf("%d%d",&N,&M);
        G.init(N);
        for(int i=0;i<N;++i){scanf("%d",&w[i]);}
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            G.Addedge(u,v,tmp);
            G.Addedge(v,u,tmp);
        }
        int q,c,s,t;
        scanf("%d",&q);
        for(int i=1;i<=q;++i){
            scanf("%d%d%d",&c,&s,&t);
            G.BFS(c,s,t);
        }
    return 0;
}
