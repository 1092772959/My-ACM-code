#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =3e5+5;
vector<int> G[maxn];
stack<int> path;
short vis[maxn];
bool FIND;
int N;

void init()
{
    FIND = false;
    for(int i=0;i<=3*N;++i)   {
        G[i].clear();
        vis[i]=0;
    }
}

void AddEdge(int u,int v)
{
    G[u].push_back(v);
}

void dfs(int v)             //寻找一条奇数长度的从S到出度为0的点的路径
{
    vis[v] = 1;
    if(G[v].size()==0 && v>N){ 
        FIND = true;
        path.push(v);
        return;
    }
    for(int i=0;i<G[v].size();++i){
        if(FIND)    
            break;
        int u = G[v][i];
        if(!vis[u]) 
            dfs(u);
    }
    if(FIND)    path.push(v);
}

bool dfs_circle(int v)         //判环
{
    if(vis[v]==2)   return true;
    vis[v]=2;
    bool ans =0;
    int u;
    for(int i=0;i<G[v].size();++i){
        u = G[v][i];
        if(!vis[u]){
            if(dfs_circle(u))  
                return true;
        }
        else if(vis[u]==2)
            return true;
    }
    vis[v]=1;
    return false;
}

int main()
{
    int M,S;
    while(~scanf("%d%d",&N,&M)){
        init();
        int k,u,v;
        for(int i=1;i<=N;++i){
            scanf("%d",&k);
            for(int j=0;j<k;++j){
                scanf("%d",&v);
                AddEdge(i,v+N);
                AddEdge(N+i,v);
                AddEdge(2*N+i,2*N+v);
            }
        }
        scanf("%d",&S);
        dfs(S);
        if(FIND){
            printf("Win\n");
            while(!path.empty()){
                u = path.top();path.pop();
                if(u>2*N) u-=2*N;
                else if(u>N)  u-=N;
                else;
                printf("%d",u);
                if(path.empty())    printf("\n");
                else printf(" ");
            }
        }
        else if(dfs_circle(2*N+S)){
            printf("Draw\n");
        }
        else{
            printf("Lose\n");
        }
    }
    return 0;
}