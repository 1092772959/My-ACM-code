#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
struct Edge{
    int v;bool w;  
};
Edge G[maxn];
vector<Edge> rG[maxn];
int pre[maxn],dfn;
bool isw[maxn];
queue<int> Q;
int res;

void init(int N){
    res=0;
    memset(pre,0,sizeof(pre));
    memset(isw,0,sizeof(isw));
    for(int i=1;i<=N;++i) rG[i].clear();
}

void AddEdge(int u,int v,bool w){
    G[u] = (Edge){v,w};
    rG[v].push_back((Edge){u,w});
}

void BFS()
{
    while(!Q.empty()){
        int u = Q.front();Q.pop();
        for(int i=0;i<rG[u].size();++i){
            Edge &e =rG[u][i];
            if(!e.w && !isw[e.v]){
                Q.push(e.v);
                isw[e.v] = true;
            }
        }       
    }
}

void Tarjan(int u){
    int v;bool w;
    pre[u]=2;
    v= G[u].v; 
    w = G[u].w;
    if(!pre[v])  
        Tarjan(v);
    else if(pre[v]==2){                   //找到环
        int cnt=0, tar,t;
        for(t=v;;t= G[t].v){
            Edge &e = G[t];
            if(e.w){
                cnt++;
                tar = G[t].v;
            }
            if(e.v==v) break;
        } 
        if(cnt==1){                    //只有一个狼边才行
            isw[tar] = true;
            Q.push(tar);
        }
    }
    pre[u]=1;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("1009.out","w",stdout);
    #endif
    int T,N,u,v,tmp;
    char op[20];
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        init(N);
        for(int u=1;u<=N;++u){
            scanf("%d %s",&v,op);
            if(op[0]=='w') AddEdge(u,v,1);
            else AddEdge(u,v,0);
        }

        for(int i =1;i<=N;++i){
            if(!pre[i]) 
                Tarjan(i);
        }
        BFS();
        for(int i=1;i<=N;++i)
            if(isw[i])  res++;
        printf("%d %d\n",0,res);
    }
    return 0;
}