#include<bits/stdc++.h>
using namespace std;
const int MAXN = 210;
const int MAXM = MAXN * MAXN;
const int INF = 0x3f3f3f3f;
queue<int>q;
int N,M;
struct Edge
{
    int v,next;
    int w;
};

struct Spfa
{
    int N,M;
    bool inq[MAXN];
    int dp[MAXN],cnt[MAXN];
    int pre[MAXN];
    int head[MAXN],tot;
    int dis[MAXN];
    bool incir[MAXN];
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

    void dfs(int pos){
        incir[pos] = true;
        for (int i = head[pos] ; i != -1 ; i = edge[i].next){
            int v = edge[i].v;
            if (!incir[v])
                dfs(v);
        }
    }

    void spfa(int s){
        memset(incir,false,sizeof(incir));
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
                if (incir[v]) continue;
                if (dis[v] > dis[u] + edge[i].w){
                    dis[v] = dis[u] + edge[i].w;
                    if (!inq[v]){
                        inq[v] = true;
                        cnt[v]++;
                        q.push(v);
                        if (cnt[v] >= N) dfs(v);
                    }
                }
            }
        }
    }
}G;
