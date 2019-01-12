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
const int MAXM = 2e5+10;
const int INF =0x3f3f3f3f;
struct Edge{
    int u,v,val;
    bool operator<(const Edge &e){return val<e.val;}
}E[MAXN];
int fa[MAXN];
int N,M;

void init(){
    for(int i=0;i<=N;++i){
        fa[i]=i;
    }
}

int Find(int x){return fa[x]==x? x:fa[x]=Find(fa[x]);}

int kruskal(int st,int ed)
{
    int ans=INF;
    for(int i=0;i<M;++i){
        init();
        for(int j=i;j<M && (E[j].val-E[i].val)<ans;++j){
            int u = E[j].u,v = E[j].v;
            u = Find(u),v =Find(v); 
            fa[u]=v;
            if(Find(st)==Find(ed))
                ans = E[j].val - E[i].val;
        }
    }
    return ans==INF? -1:ans;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,Q,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            E[i] = (Edge){u,v,tmp};
        }     
        sort(E,E+M);
        scanf("%d",&Q);
        while(Q--){
            scanf("%d%d",&u,&v);
            printf("%d\n",kruskal(u,v));
        }
    }
    return 0;
}