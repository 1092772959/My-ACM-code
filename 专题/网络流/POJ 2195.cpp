#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
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

void AddEdge(int u, int v, int cap, int cost)
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


struct Node{
    int x,y;  
}Hz[MAXN],Pz[MAXN];
char str[MAXN]; 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int H,W;
    while(scanf("%d %d",&H,&W)==2){
        if(!H && !W) continue;
        int nh=0,np=0;
        for(int i=1;i<=H;++i){
            scanf("%s",str+1);
            for(int j=1;j<=W;++j){
                char c = str[j];
                if(c=='H'){
                    Hz[++nh] = (Node){i,j};
                }
                else if(c=='m'){
                    Pz[++np] = (Node){i,j};
                }
            }
        }
        int st = 0,  ed = np+nh*2+1;
        init(ed+1);
        for(int i =1;i<=np;++i){
            for(int j=1;j<=nh;++j){
                int dist = abs(Pz[i].x-Hz[j].x) + abs(Pz[i].y - Hz[j].y);
                AddEdge(i,j+np,1,dist);
            }
        }
        for(int i=1;i<=nh;++i){
            AddEdge(i+np,i+nh+np,1,0);
            AddEdge(i+nh+np,ed,1,0);
        }
        for(int i=1;i<=np;++i){
            AddEdge(st,i,1,0);
        }
        int cost;
        int res = minCostMaxflow(st,ed,cost);
        printf("%d\n",cost);
    }
    return 0;
}