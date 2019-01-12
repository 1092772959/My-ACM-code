#include<bits/stdc++.h>
using namespace std;
typedef int LL;
const int maxn =1e2+5,maxm = 1e4+5;
const LL INF =0x3f3f3f3f;
struct Edge{
    int to,next;
    LL val;
};
struct Node{
    int u,tag;
};
struct SPFA{
    int n,m,tot;
    Edge edges[maxm];
    int head[maxn];
    LL dis[maxn][2];            //最短路和次短路长度
    bool vis[maxn][2];
    int cnt[maxn][2];           //最短路和次短路条数

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
    void spfa(int s){
        for(int i=0;i<=n;++i){
            dis[i][0]=INF,cnt[i][0]=0;
            dis[i][1]=INF,cnt[i][1]=0;
            vis[i][0]=vis[i][1]=false;    
        }
        dis[s][0]=0,cnt[s][0]=1;
        queue<Node> Q;
        Q.push((Node){s,0});
        while(!Q.empty()){
            Node x =Q.front();Q.pop();
            int u = x.u,tag = x.tag;
            if(vis[u][tag]) continue;
            vis[u][tag] = true;
            for(int i=head[u];~i;i=edges[i].next){
                int v =edges[i].to,w =edges[i].val;
                int tmp = dis[u][tag] + w;
                if(dis[v][0]>tmp) {      //需要更新最短路
                    if(dis[v][0]!=INF){     //将次短路覆盖
                        dis[v][1] = dis[v][0];
                        cnt[v][1] = cnt[v][0];
                        Q.push((Node){v,1});
                    }
                    dis[v][0]=tmp;
                    cnt[v][0]=cnt[u][tag];
                    Q.push((Node){v,0});
                }
                else if(dis[v][0]==tmp){        //最短路长度不变，数量增加
                    cnt[v][0]+=cnt[u][tag];
                }
                else if(dis[v][1]>tmp){         //次短路长度改变
                    dis[v][1] = tmp;
                    cnt[v][1] = cnt[u][tag];
                    Q.push((Node){v,1});
                }
                else if(dis[v][1]==tmp){        //次短路长度不变，数量增加
                    cnt[v][1]+=cnt[u][tag];
                }
            }
        }
    }
}G;
