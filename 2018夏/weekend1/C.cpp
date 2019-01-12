#include<bits/stdc++.h>
using namespace std;
const int N =1e4+5;
const int M = 1e6+5;

bool vis[M];
int pre[M];
vector<int> G[N];
queue<int> Q;


void add_edge(int u,int v)
{
    G[u].push_back(v);
}

int dfs(int u)
{
    int i,v;
    for(i=0;i<G[u].size();i++){
        v = G[u][i];
        if(!vis[v]){
            vis[v]=1;
            Q.push(v);
            if(pre[v]==-1||dfs(pre[v])){
                pre[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int res=0;
    memset(pre,-1,sizeof(pre));
    for(int i=1;i<=1e4;i++){
        while(!Q.empty()){
            vis[Q.front()]= false;
            Q.pop();
        }
        if(dfs(i)) res++;
        else break;
    }
    return res;
 }

int main()
{
    int n,u,v;
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;++i){
            scanf("%d%d",&u,&v);
            add_edge(u,i);
            add_edge(v,i);
        }
        printf("%d\n",maxmatch());
    }
    return 0;
}