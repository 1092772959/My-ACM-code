#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
struct node { int from,to,len;} edge[maxn];
int N,fa[maxn],M,q;
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
    sort(edge,edge+M,cmp);
    for(int i=0;i<=N;i++) fa[i]=i;
    int ans=0;
    for(int i=0;i<M;i++)
        if(Find(edge[i].from)!=Find(edge[i].to)){
            Merge(edge[i].from,edge[i].to);
            ans+=edge[i].len;
        }
    return ans;
}
