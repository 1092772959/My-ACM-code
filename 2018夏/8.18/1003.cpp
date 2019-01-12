#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int maxn =1e5+5;
const LL mod = 1e9+7;
struct Edge{
    int v,next;
}edges[maxn<<2];
int head[maxn],tot;
bool vis[maxn];
void init()
{
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    tot =0 ;
}

void AddEdge(int u,int v)
{
    edges[tot] = (Edge){v,head[u]};
    head[u] = tot++;
}

LL res[maxn];
int cnt;
LL val[maxn];
LL ans;
LL bit[50];
void dfs(int u)
{
    vis[u] =true;
    res[cnt++] = val[u];
    for(int i =head[u];~i;i=edges[i].next){
        int v = edges[i].v;
        if(vis[v]) continue;
        dfs(v);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M;
    int u,v;
    int T; scanf("%d",&T);
    while(T--){
        ans = 0;
        scanf("%d%d",&N,&M);
        init();
        for(int i=1;i<=N;++i)
            scanf("%lld",&val[i]);
        while(M--){
            scanf("%d%d",&u,&v);
            if(u==v) continue;
            AddEdge(u,v);
            AddEdge(v,u);
        }
        for(int i=1;i<=N;++i){
            if(!vis[i]){
                cnt=0;
                dfs(i);
                sort(res,res+cnt);

                if(cnt==1) continue;            //一个点没必要

                memset(bit,0,sizeof(bit));
                int pos = 0;
                for(int i=0;i<cnt;++i){
                    LL tmp = res[i];
                    LL tag;
                    for(int j=0;j<40;++j){
                        tag = (1LL<<j);
                        if(tag&tmp){
                            ans =(ans+(tmp*tag%mod)*bit[j]%mod)%mod;
                            bit[j]++;
                        }
                    }
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}