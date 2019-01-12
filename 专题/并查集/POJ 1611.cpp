#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 3e4+5;
const int INF= 0x3f3f3f3f;
int f[maxn];
bool vis[maxn];
void init(int N)
{
    for(int i=0;i<=N;++i)   f[i]=i,vis[i]=false;
}

int Find(int x)
{
    return x==f[x]? x: f[x] = Find(f[x]);
}

void Union(int x,int y)
{
    x = Find(x),y = Find(y);
    if(x!=y) f[x] = y;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        init(N);
        vis[0]=true;
        for(int i=1;i<=M;++i){
            scanf("%d",&K);
            scanf("%d",&u);
            K--;
            u = Find(u);
            while(K--){
                scanf("%d",&v);
                v = Find(v);
                if(vis[v]) vis[u] = true;
                if(vis[u]) vis[v] = true;
                Union(u,v);
            }
        }
        int res=0;
        for(int i=0;i<N;++i){
            if(vis[Find(i)])
                res++;
        }
        printf("%d\n",res);
    }
    return 0;
}
