//割点/边

#include<bits/stdc++.h>
using namespace std;
const int maxn =1e2+5;
typedef pair<int,int> PII;
vector<int> G[maxn];
vector<PII> res;
int pre[maxn],low[maxn],f[maxn],dfn;

void init(int n)
{
    dfn=0;
    res.clear();
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(f,-1,sizeof(f));
    for(int i=0;i<=n;++i){
        G[i].clear();
    }
}

void dfs(int u,int fa)
{
    f[u]=fa;
    low[u]=pre[u]= ++dfn;
    int child = 0;
    for(int i=0;i<G[u].size();++i){
        int v= G[u][i];
        /*if(v==fa && !child){        //解决重边和反向边的叠加
            child++;
            continue;
        }*/
        if(!low[v]){
            dfs(v,u);
            low[u] = min(low[u],low[v]);
        }
        else if(fa!=v) {
            low[u] = min(low[u],pre[v]);
        }
    }
}

int main()
{
    int N,M,u,v,tmp;
    while(~scanf("%d",&N)){
        init(N);
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

        for(int i=0;i<N;++i){
            int v = f[i];
            if(v!=-1 && pre[v]<low[i]){
                int t1 = min(v,i),t2=max(v,i);
                res.push_back(make_pair(t1,t2));       
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