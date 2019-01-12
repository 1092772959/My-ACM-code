#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to, next, cap, flow, cost;
} edge[MAXM];
int head[MAXN], tot;
int pre[MAXN], dis[MAXN];
bool vis[MAXN];
int N;                  //0~N-1的点数
void init(int n)
{
    N = n;
    tot = 0;
    memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, int cap, int cost)
{
    edge[tot] = (Edge){v,head[u],cap,0,cost};
    head[u] = tot++;
    edge[tot] = (Edge){u,head[v],0,0,-cost};
    head[v] = tot++;
}

bool spfa(int s, int t){
    queue<int> q;
    for (int i = 0; i < N; i++){
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;

            if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost){
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (pre[t] == -1) return false;
    else  return true;
}

int minCostMaxflow(int s, int t, int &cost){
    int flow = 0;
    cost = 0;
    while (spfa(s, t)){
        int Min = INF;
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]){
            if (Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]){
            edge[i].flow += Min;
            edge[i ^ 1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}
