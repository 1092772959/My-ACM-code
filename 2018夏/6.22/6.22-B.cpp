#include<bits/stdc++.h>
using namespace std;
const int maxn =1e2+5;
int n;

//以行或者列列相同。并查集
struct Node{
    int x,y;
}s[maxn];

int f[maxn];

void init()
{
    for(int i=0;i<n;++i)   f[i]=i;
}

int Find(int x)
{
    return x==f[x]? x:f[x]=Find(f[x]);
}

void unite(int x,int y)
{
    int fx = Find(x);
    int fy = Find(y);
    if(fx!=fy){
        f[fx]=fy;
    }
}

int solve()
{
    int res=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<i;++j){
            if(s[i].x == s[j].x || s[i].y==s[j].y){
                unite(i,j);
            }
        }
    }
    for(int i=0;i<n;++i){
        if(Find(i)==i){
            res++;
        }
    }
    return res-1;
}

int main()
{
    while(~scanf("%d",&n)){
        init();
        for(int i=0;i<n;++i){
            scanf("%d%d",&s[i].x,&s[i].y);
        }        
        printf("%d\n",solve());
    }
    return 0;
}