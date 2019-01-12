#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 2e5+5;
const int INF= 0x3f3f3f3f;
int dist[maxn];
int fa[maxn];

void init(int N)
{
    for(int i=1;i<=N;++i){
        fa[i]=  i;
        dist[i]=0;
    }
}

int Find(int x)
{
    if(fa[x]==x) return x;
    int f =fa[x];
    fa[x] = Find(fa[x]);                //路径压缩，但是要维护到根结点的距离
    dist[x] +=dist[f];
    return fa[x];
}

bool Union(int a,int b,int d)
{
    int roota = Find(a),rootb = Find(b);
    if(roota == rootb){
        if(d+dist[a]!=dist[b]) return false;        
    }
    fa[rootb] = roota;
    dist[rootb] = d - dist[b]+dist[a]; 
    return true;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%d%d",&N,&M)==2){
        init(N);
        int res=0;
        while(M--){
            scanf("%d%d%d",&u,&v,&tmp);
            u--;
            if(!Union(u,v,tmp)) res++;
        }
        printf("%d\n",res);
    }
    return 0;
}
