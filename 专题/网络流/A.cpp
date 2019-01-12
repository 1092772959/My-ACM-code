#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<vector>  
#include<queue>  
using namespace std;  
const int INF=0x3f3f3f3f;  
const int maxn = 1e2+5;

bool vis[maxn];
struct Edge{int from, to,cap,flow; };
struct Dinic{
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
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x,int a)
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
}F;
int a[maxn][maxn],n,p;
int s,t;  
void build()  
{  
    //建图拆点，其中1-n是入点，n+1-2n是出点  
    for(int i=1;i<=n;i++){  
        F.AddEdge(i,n+i,a[i][0]); //出点指向入点，容量是生产量  
        bool flag=1;  
        for(int j=1;j<=p;j++)if(a[i][j]==1){flag=0;break;}  
        if(flag)F.AddEdge(s,i,INF); //超源点指向入点，容量无限  
        flag=1;  
        for(int j=p+1;j<2*p+1;j++)if(a[i][j]!=1){flag=0;break;}  
        if(flag)F.AddEdge(n+i,t,INF); //出点指向超汇点，容量无限  
        for(int j=1;j<=n;j++){  
            if(i==j)continue;  
            flag=1;  
            for(int k=1;k<=p;k++)if(a[j][k]!=2&&a[j][k]!=a[i][k+p]){flag=0;break;}  
            if(flag)F.AddEdge(n+i,j,INF); 
        }  
    }    
}  
int main()  
{  
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d%d",&p,&n)==2){  
        for(int i=1;i<=n;i++)  
            for(int j=0;j<2*p+1;j++)
                scanf("%d",&a[i][j]);  
        s=0,t=2*n+1;
        F.init(t+1);  
        build();  
        int res=F.MaxFlow(s,t);  
        int tot=0;  
        int ans[maxn][3];  
        for(int u=n+1;u<t;u++)
            for(int i=0;i<F.G[u].size();i++){  
                Edge& e=F.edges[F.G[u][i]];  
                if(e.to>0&&e.to<=n&&e.flow>0)
                    ans[tot][0]=u-n,ans[tot][1]=e.to,ans[tot++][2]=e.flow;  
        }
        printf("%d %d\n",res,tot);  
        for(int i=0;i<tot;i++)printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);  
    }
    return 0;  
}  
