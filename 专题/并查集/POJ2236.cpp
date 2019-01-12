#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e3+5;
const int INF= 0x3f3f3f3f;
int fa[maxn];
int x[maxn],y[maxn];
bool vis[maxn];
int d;

void init(int N)
{
    for(int i=1;i<=N;++i){ 
        fa[i]=i;
        vis[i]=false;
    }
}

int Find(int x)
{
    return x==fa[x] ? x: fa[x] = Find(fa[x]);
}

void Union(int x,int y)
{
    x = Find(x),y= Find(y);
    if(x!=y){
        fa[y] = x;
    }
}

bool check(int i,int j)
{
    int dx = x[i]-x[j],dy= y[i]- y[j];
    return sqrt((double)dx*dx+dy*dy)<=d;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,Q,u,v,tmp,K;
    char c;
    scanf("%d%d",&N,&d);
    init(N);
    for(int i=1;i<=N;++i)
        scanf("%d%d",&x[i],&y[i]);
    while(getchar(),scanf("%c",&c)!=EOF){
        if(c=='O'){
            scanf("%d",&u);
            if(!vis[u]){
                for(int i=1;i<=N;++i){
                    if(!vis[i]) continue;
                    if(check(u,i)) Union(u,i);
                }
                vis[u] = true;
            }
        }
        else{
            scanf("%d%d",&u,&v);
            int fu = Find(u),fv =Find(v);
            if(fu==fv && vis[u] &&vis[v]) printf("SUCCESS\n");
            else printf("FAIL\n");
        }
    }
    return 0;
}
