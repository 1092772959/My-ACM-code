#include<bits/stdc++.h>
using namespace std;
const int maxn =3e5+10;
int N,M;
vector<int> G[maxn];
vector<int> topo;
int indeg[maxn];
int dp[maxn][28];
char str[maxn];

void init()
{
    topo.clear();
    memset(indeg,0,sizeof(indeg));
    for(int i=0;i<=N;++i)   G[i].clear();
}

bool circle()
{
    int v,u,cnt=0;
    queue<int> Q;
    for(int i=1;i<=N;++i){
        if(!indeg[i]){
            Q.push(i);
            cnt++;
        }
    }
    while(!Q.empty()){
        v= Q.front(); Q.pop();
        topo.push_back(v);
        for(int i=0;i<G[v].size();++i){
            u =G[v][i];
            indeg[u]--;
            if(!indeg[u]){ 
                Q.push(u);
                cnt++;
            }
        }                
    }
    if(cnt==N) return false;
    else return true;
}

int solve(int key)
{
    memset(dp,0,sizeof(dp));
    int res=0;
    int e,v,u;
    for(int i =0;i<topo.size();++i){
        v =topo[i];
        e = str[v]-'a';
        if(e==key)
            dp[v][e]++;
        res = max(res,dp[v][key]);
        for(int j = 0;j<G[v].size();++j){
            u = G[v][j];
            dp[u][key]= max(dp[u][key],dp[v][key]);
        }
    }
    return res;
}

int main()
{
    int v,u;
    while(~scanf("%d%d",&N,&M)){
        init();
        scanf("%s",str+1);
        for(int i=0;i<M;++i){
            scanf("%d%d",&v,&u);
            G[v].push_back(u);
            indeg[u]++;        
        }
        if(circle()){
            printf("-1\n");
            continue;
        }
        int res=0;
        for(int i=0;i<26;++i){
            res=max(res,solve(i));
        }
        printf("%d\n",res);
    }
    return 0;
}