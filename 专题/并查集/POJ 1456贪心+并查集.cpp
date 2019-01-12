#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const int INF= 0x3f3f3f3f;

struct Node{
    int w,ed;
    bool operator <(const Node& p) const {return w>p.w;}
}p[maxn];
int fa[maxn];
void init(int N) {for(int i=0;i<=N;++i) fa[i]=i;}
inline int Find(int x)  {return fa[x]==x ? x:fa[x] = Find(fa[x]);}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    int a,b;
    while(scanf("%d",&N)==1){
        init(10000);
        for(int i=0;i<N;++i) scanf("%d%d",&p[i].w,&p[i].ed);
        sort(p,p+N);
        int res=0;
        for(int i=0;i<N;++i){
            int d = Find(p[i].ed);
            if(d>0){
                res+=p[i].w;
                fa[d] = d-1;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}