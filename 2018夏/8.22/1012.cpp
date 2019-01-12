#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to, next, cap, flow, cost;
} edge[MAXM];
int head[MAXN], tol;
int pre[MAXN], dis[MAXN];
bool vis[MAXN];
int N;                  //0~N-1的点数
void init(int n)
{
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cap, int cost)
{
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
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

int n,M,K,W;

struct Node{
    int s,t,op,val;
}pt[MAXN];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d %d %d %d",&n, &M, &K, &W);
        int st = 0,big =2*M+1;
        int ed = big+1;
        init(2*M+3);
        addedge(big,st,K,0);
        for(int i=1;i<=M;++i){
            scanf("%d%d%d%d",&pt[i].s,&pt[i].t, &pt[i].val, &pt[i].op);
            addedge(st,i,1,-pt[i].val);
            addedge(i+M,ed,1,0);
            addedge(i,i+M,1,0);
        }
        for(int i=1;i<=M;++i){
            for(int j=1;j<=M;++j){
                if(i==j) continue;
                if(pt[i].t<=pt[j].s){
                    if(pt[i].op^pt[j].op){
                        addedge(i+M,j,1,-pt[j].val);
                    }
                    else{
                        addedge(i+M,j,1,-(pt[j].val-W));
                    }
                }
            }
        }
        int res;
        minCostMaxflow(big,ed,res);
        printf("%d\n",-res);
    }
    return 0;
}