//割点/边
#include<bits/stdc++.h>
using namespace std;
const int maxn =1e3+5,maxm = 1e6+6,INF=0x3f3f3f3f;
int pre[maxn],low[maxn],head[maxn],dfn,top,tot;
int res;
struct Edge{
    int to,next;
    int val;
    bool cut;
}edges[maxm<<2];

void init()
{
    dfn=tot=top=0;
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int val)
{
    edges[top].to =v;
    edges[top].val = val;
    edges[top].next  =head[u];
    edges[top].cut = false;
    head[u] = top++;
}

void dfs(int u,int fa)
{
    low[u]=pre[u]= ++dfn;
    for(int i=head[u];i!=-1;i=edges[i].next){
        int v= edges[i].to;
        if(i==(fa^1)) continue;
        if(!low[v]){
            dfs(v,i);
            low[u] = min(low[u],low[v]);
            if(low[v]>pre[u]){
                edges[i].cut = edges[i^1].cut=true;
                tot++;
            }
        }
        else
            low[u] = min(low[u],pre[v]);
    }
}

int main()
{
    int N,M,u,v,tmp;
    while(~scanf("%d%d",&N,&M)){
        if(N+M==0) break;
        init();
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            AddEdge(u,v,tmp);
            AddEdge(v,u,tmp);
        }
        int cc=0;
        for(int i=1;i<=N;++i)
            if(!pre[i]){
                dfs(i,-1);
                cc++;
            }
                
        if(!tot) {printf("-1\n");continue;}

        res=INF;
        for(int i=0;i<top;i+=2){
            if(edges[i].cut && edges[i].val<res){
                res = edges[i].val;
            }
        }
        //坑
        if(res==0)  res=1;
        else if (cc>1)  res=0;
        else;
        printf("%d\n",res);
    }   
    return 0;
}
