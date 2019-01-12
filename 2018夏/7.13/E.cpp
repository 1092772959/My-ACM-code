#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const LL INF = (LL)1<<60;

struct Edge{
    int from,to;
    LL val;
};

struct HeapNode{
    LL d;
    int u;
    bool operator <(const HeapNode &rhs) const {return d>rhs.d;}
};

vector<Edge> edges;
vector<int> G[maxn];
bool used[maxn];
LL d[maxn];
int p[maxn];

struct Dijsra{
    int n,m;

    void init(int n){
        this-> n =n;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
        memset(p,-1,sizeof(p));
    }

    void AddEdge(int from,int to,LL dist){
        edges.push_back((Edge){from,to,dist});
        m = edges.size();
        G[from].push_back(m-1);
    }

    bool dijkstra(int s,LL stop){
        priority_queue<HeapNode> Q;
        for(int i=0;i<=n;++i) d[i]=INF;
        memset(used,0,sizeof(used));
        d[s] =0;
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x = Q.top(); Q.pop();
            int u =x.u;
            if(used[u]) continue;
            used[u]= true;
            for(int i=0;i<G[u].size();++i){
                Edge & e = edges[G[u][i]];
                if(d[e.to]>d[u]+e.val && e.val<=stop){
                    d[e.to] = d[u]+e.val;
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
        if(d[n] == INF) return false;
        else return true;
    }
}go;

int N,M;

int main()
{
    int u,v;
    LL tmp;
    int X;
    long double limit;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>N>>M>>X){
        go.init(N);
        for(int i=1;i<=M;++i){
            cin>>u>>v>>tmp;
            go.AddEdge(u,v,tmp);
            go.AddEdge(v,u,tmp);
        }

        go.dijkstra(1,INF);

        limit = (long double)(d[N]*(1.0+X/100.0));

        LL low=0,high = d[N],mid,res;
        while(low<=high){
            mid = low+(high-low)/2;
            if(go.dijkstra(1,mid) &&(long double)(d[N])<=limit){
                high = mid-1;
            }
            else
                low = mid+1;
        }
        cout<<low<<endl;
    }
    return 0;
}

/*
2 1 100
1 2 5

9 8 15
1 9 16
1 4 49 8 15
1 9 16
1 4 4
4 5 4
5 6 4
6 8 4
4 7 5
7 8 5
8 9 4

4 5 4
5 6 4
6 8 4
4 7 5
7 8 5
8 9 4

9 8 30
1 9 16
1 4 4
4 5 4
5 6 4
6 8 4
4 7 5
7 8 5
8 9 4

*/
