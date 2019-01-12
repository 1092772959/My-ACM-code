#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
typedef long long LL;
using namespace std;
const int maxn =5e2+5;
const int maxm = 4e4+5;
struct Edge{
    int v,next;
}edge[maxm];
int head[maxn],tot,cnt;
int ind[maxn];
void init()
{
    memset(ind,0,sizeof(ind));
    memset(head,-1,sizeof(head));
    tot=0;
}

void AddEdge(int u,int v)
{
    edge[tot] = (Edge){v,head[u]};
    head[u] = tot++;   
}

int ans[maxn];
bool topo(int n)
{
    cnt=n;
    priority_queue<int> Q;
    for(int i =1;i<=n;++i){
        if(!ind[i]){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int u = Q.top() ;Q.pop();
        ans[u] = cnt--;
        for(int i=head[u];~i;i=edge[i].next){
            int v = edge[i].v;
            ind[v]--;
            if(!ind[v]){
                Q.push(v);
            }
        }
    }
    if(cnt!=0) return false;
    else return true;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M,m,q,u,v,cas=1;
    int T; scanf("%d",&T);
    while(T--){
        init();
        bool flag = false;
        scanf("%d%d",&N,&M);
        while(M--){
            scanf("%d%d",&v,&u);
            AddEdge(u,v);
            ind[v]++;
        }
        if(!topo(N)) printf("-1\n");
        else{
            for(int i=1;i<N;++i){
                printf("%d ",ans[i]);
            }
            printf("%d\n",ans[N]);
        }
    }
    return 0;
}
