#include<stack>
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
typedef long long LL;
const int MAXN = 1e3+10;
int fa[MAXN];
int res;
void init(int N){
    res= N-1;
    for(int i=0;i<=N;++i)
        fa[i]=i;
}

int Find(int x) {return x==fa[x]?x:fa[x]=Find(fa[x]);}

void Union(int x,int y )
{
    x = Find(x),y =Find(y);
    if(x!=y) {
        fa[x]=y;
        res--;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v;
    while(scanf("%d%d",&N,&M)==2){
        init(N);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            Union(u,v);
        }
        printf("%d\n",res);
    }
    return 0;
}
