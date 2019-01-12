#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
int a[maxn];
int res[maxn];
vector<int> G[maxn];
bool vis[maxn];
int d[maxn][305];
void init(int N)    {for(int i=1;i<=N;++i) G[i].clear();}
void AddEdge(int u,int v){G[u].push_back(v);}

void BFS(int val,int N)
{
    memset(vis,0,sizeof(vis));
    queue<int> Q;
    for(int i=1;i<=N;++i){
        if(a[i]==val){
            vis[i]=true;
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int x =Q.front();Q.pop();
        for(int i=0;i<G[x].size();++i){
            int v = G[x][i];
            if(!vis[v]){
                vis[v] = true;
                d[v][val] = d[x][val]+1;
                Q.push(v);
            }
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M,K,S,u,v;
    while(scanf("%d%d%d%d",&N,&M,&K,&S)==4){
        init(N);
        memset(d,0,sizeof(d));
        for(int i=1;i<=N;++i) scanf("%d",&a[i]);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        for(int i=1;i<=K;++i){
            memset(vis,0,sizeof(vis));
            BFS(i,N);
        }
        for(int i=1;i<=N;++i){
            sort(d[i]+1,d[i]+K+1);
            res[i]=0;
            for(int j =1;j<=S;++j){
                res[i]+=d[i][j];
            }
        }
        for(int i=1;i<N;++i) printf("%d ",res[i]);
        printf("%d\n",res[N]);
    }
    return 0;
}