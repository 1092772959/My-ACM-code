#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
const int INF= 0x3f3f3f3f;
int fa[maxn];

void init(int N)
{
    for(int i=0;i<=N;++i) fa[i]=-i;
}

inline int Find(int x){
    return fa[x]==x? x:fa[x]= Find(fa[x]);
}

bool Union(int x,int y)
{
    x= Find(x),y=Find(y);
    if(x!=y) fa[x]=y;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K,cas=1;
    while(scanf("%d%d",&u,&v)==2){
        if(!u) {printf("Case %d is a tree.\n",cas++);continue;}
        if(u==-1) break;
        init(105);
        bool flag= true;
        if(u==v) flag=  false;
        fa[u]=fa[v]=v;
        while(scanf("%d%d",&u,&v)==2){
            if(!u) break;
            if(!flag) continue;
            if(fa[u]<0)  fa[u]=-fa[u];
            if(fa[v]<0) fa[v]=-fa[v];
            u = Find(u),v = Find(v);
            if(u==v) flag = false;
            else Union(u,v);
        }
        int cnt=0;
        for(int i=1;i<=105;++i) if(fa[i]>0 && Find(i)==i) cnt++;
        printf("Case %d ",cas++);
        if(flag && cnt==1) printf("is a tree.\n");
        else printf("is not a tree.\n");
    }
    return 0;
}