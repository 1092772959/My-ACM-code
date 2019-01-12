#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
struct node { int from,to,len;} edge[maxn];
int n,fa[maxn],m,ans,q;
bool cmp(node a,node b) { return a.len<b.len; }
int Find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=Find(fa[x]);
}
void Merge(int x,int y)
{
    x=Find(x),y=Find(y);
    if(x!=y) fa[y]=x;
}
int kruskal()
{
    sort(edge,edge+m,cmp);
    for(int i=0;i<=n;i++) fa[i]=i;
    ans=0;
    int cnt=0;
    for(int i=0;i<m;i++)
        if(Find(edge[i].from)!=Find(edge[i].to)){
            Merge(edge[i].from,edge[i].to);
            ans+=edge[i].len;
        }
    return ans;
}


#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,u,v,tmp,k;
    while(scanf("%d",&N)==1){
        if(!N) break;
        int M = N*(N-1)/2;
        n=N,m=M;
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            edge[i].from = u,edge[i].to =v,edge[i].len = tmp;
        }
        printf("%d\n",kruskal());
    }
    return 0;
}