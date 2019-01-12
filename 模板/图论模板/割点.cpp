//割点/边

#include<bits/stdc++.h>
using namespace std;
const int maxn =1e2+5;
typedef pair<int,int> PII;
vector<int> G[maxn];
vector<PII> res;
int pre[maxn],low[maxn],iscut[maxn],dfn;

void init(int n)
{
    dfn=0;
    res.clear();
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    for(int i=0;i<=n;++i){
        G[i].clear();
    }
}

int dfs(int u,int fa)
{
    int lowu = pre[u]= ++dfn;
    int child = 0;
    for(int i=0;i<G[u].size();++i){
        int v= G[u][i];
        if(!pre[v]){
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv>=pre[u]){
                iscut[u]=true;
            }
        }
        else if(pre[v]<pre[u] && v!=fa){
            lowu = min(lowu,pre[v]);
        }
    }
    if(fa<0 && child==1)   iscut[u]=false;
    low[u]=lowu;
    return lowu;
}

int main()
{
    int N,M,u,v,tmp;
    while(~scanf("%d",&N)){
        init(N);
        if(!N){  
            printf("0 critical links\n\n");
            break;
        }
        for(int i=0;i<N;++i){
            scanf("%d (%d)",&u,&tmp);
            for(int j=0;j<tmp;++j){
                scanf("%d",&v);
                G[u].push_back(v);
            }
        }
        for(int i=0;i<N;++i){
            if(!pre[i]){
                dfs(i,-1);
            }
        }
        sort(res.begin(),res.end());
        printf("%d critical links\n",res.size());
        for(int i=0;i<res.size();++i){
            printf("%d - %d\n",res[i].first,res[i].second);
        }
        printf("\n");
    }   
    return 0;
}

//