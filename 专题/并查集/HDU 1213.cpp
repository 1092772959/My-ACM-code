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
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        init(N);
        while(M--){
            scanf("%d%d",&u,&v);
            Union(u,v);
        }
        for(int i=1;i<=N;++i){
            vis[Find(i)] = true;
        }
        int res=0;
        for(int i=1;i<=N;++i){
            if(vis[i]) res++;
        }
        printf("%d\n",res);
    }
    return 0;
}
