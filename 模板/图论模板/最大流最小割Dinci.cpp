#include<bits/stdc++.h>
using namespace std;
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef pair<int,int> PII;

const int INF = 0x3f3f3f3f;
const int maxn = 1e3+5;

bool vis[maxn];
struct Edge{
    int from, to,cap,flow;  //Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f) {}
};

struct Dinic
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

    void init(int n){
        this->n = n;
        for(int i=0;i<=n;++i){
            G[i].clear();
        }
        edges.clear();
    }

    void AddEdge(int from,int to,int cap){
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS(){
        memset(vis,0,sizeof(vis));
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int i=0;i<G[x].size();i++){
                Edge &e = edges[G[x][i]];
                if(!vis[e.to] && e.flow < e.cap){
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;//层次图
                    q.push(e.to);
                }
            }
        }
        return vis[t];//能否到汇点，不能就结束
    }
    int DFS(int x,int a)//x为当前节点，a为当前最小残量
    {
        if(x == t || a == 0) return a;
        int flow = 0 , r;
        for(int& i = cur[x];i < G[x].size();i++){
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (r = DFS(e.to , min(a,e.cap - e.flow) ) ) > 0 ){
                e.flow += r;
                edges[G[x][i] ^ 1].flow -= r;
                flow += r;//累加流量
                a -= r;
                if(a == 0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s,int t){
        this->s = s; this->t = t;
        int flow = 0;
        while(BFS()){
            memset(cur,0,sizeof(cur));
            flow += DFS(s,INF);
        }
        return flow;
    }

    void mincut(int s,int t){
        MaxFlow(s,t);
        queue<int> Q;
        Q.push(s);
        memset(vis,0,sizeof(vis));
        vis[s]=true;
        map<PII,bool> S;
        while(!Q.empty()){
            int x= Q.front();
            Q.pop();
            for(int i=0;i<G[x].size();++i){
                Edge & e= edges[G[x][i]];
                if(!vis[e.to] && e.flow <e.cap){
                    vis[e.to] = true;
                    Q.push(e.to);
                }
            }
        }
        for(int i=1;i<=n;++i){
            if(vis[i]){
                for(int j=0;j<G[i].size();++j){
                    Edge & e = edges[G[i][j]];
                    if(!vis[e.to] && !S[mp(i,e.to)]){
                        printf("%d %d\n",i,e.to);
                        S[mp(i,e.to)] = 1;
                    }
                }
            }
        }
    }
}F;
