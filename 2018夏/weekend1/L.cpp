#include<bits/stdc++.h>
using namespace std;
const int maxn =1e6+5;
int n,m;
int a[maxn];
int f[maxn];
priority_queue<int> Q[maxn];

void init()
{
    for(int i=0;i<=n;++i)   f[i]=i;
}

int Find(int x)
{
    return x==f[x]?x:f[x]= Find(f[x]);
}

void Union(int x,int y)
{
    int fx = Find(x);
    int fy = Find(y);
    if(fx!=fy){
        f[fx]= fy;
    }
}

void solve()
{
    for(int i=1;i<=n;++i){
        Q[Find(i)].push(a[i]);
    }
    for(int i=1;i<n;++i){
        printf("%d ",Q[Find(i)].top());
        Q[Find(i)].pop();
    }
    printf("%d\n",Q[Find(n)].top());
    Q[Find(n)].pop();
}

int main()
{
    while(~scanf("%d%d",&n,&m)){
        int p,q;
        init();
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        for(int i=0;i<m;++i){
            scanf("%d%d",&p,&q);
            Union(p,q);
        }
        solve();
    }
    return 0;
}