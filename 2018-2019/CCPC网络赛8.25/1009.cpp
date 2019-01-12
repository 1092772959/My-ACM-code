#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+9;
const int mod=1e9+7;
#define inf 0x3f3f3f3f
int n,m;
int num;
int head[maxn];
int size[maxn];
ll fac[maxn];
ll ans;
ll dp[maxn];
void Fac()
{
    fac[0]=1;
    fac[1]=1;
    for(int i=2;i<maxn;i++)
    {
        fac[i]=fac[i-1]*i%mod;
    }
}
struct Edge
{
    int u,v,next,w;
}edge[maxn<<2];
void addEdge(int u,int v,int w)
{
    edge[num].u=u;
    edge[num].v=v;
    edge[num].w=w;
    edge[num].next=head[u];
    head[u]=num++;
}
void init()
{
    num=0;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
}
void dfs(int u,int pre)
{
    size[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].v,w=edge[i].w;
        if(v==pre) continue;
        dfs(v,u);
        size[u]+=size[v];
        dp[u]=((dp[u]+dp[v])%mod+1ll*size[v]*(n-size[v])%mod*1ll*w)%mod;
    }
}
int main(int argc, char const *argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    Fac();
    while(scanf("%d",&n)!=EOF)
    {
        init();
        for(int i=1;i<n;i++)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            addEdge(x,y,w);
            addEdge(y,x,w);
        }
        dfs(1,0);
        ll ans=dp[1];
        ans=ans*fac[n-1]%mod*2%mod;
        cout<<ans<<endl;
    }
    return 0;
}