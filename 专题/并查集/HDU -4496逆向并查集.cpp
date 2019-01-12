#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e4+5;
const int INF= 0x3f3f3f3f;
struct OP{int u,v; }p[maxn*10];
int fa[maxn];
int ans[maxn*10];
void init(int N){ for(int i=0;i<=N;++i) fa[i]=i;}
inline int Find(int x){return fa[x]==x? x:fa[x]= Find(fa[x]);}
void Union(int a,int b){
    a = Find(a), b= Find(b);
    if(a!=b) fa[a]= b;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K,cas=1;
    while(scanf("%d%d",&N,&M)==2){
        init(N);
        for(int i=1;i<=M;++i) scanf("%d%d",&p[i].u,&p[i].v);
        int res=N;
        for(int i=M;i>=1;--i){
            int u = p[i].u, v= p[i].v;
            u = Find(u),v = Find(v);
            ans[i] = res;
            if(u!=v){
                Union(u,v);
                res--;
            }
        }
        for(int i=1;i<=M;++i) printf("%d\n",ans[i]);
    }
    return 0;
}