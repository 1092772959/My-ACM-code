#include<bits/stdc++.h>
using namespace std;
const int maxn =2e5+5;
vector<int> G[maxn];
bool vis[maxn];
int cnt[maxn];
int N,M,Q,S;

void init(int N)
{
    for(int i=0;i<=N;++i) G[i].clear();
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(vis));
}

void dfs(int u)
{
    vis[u] = true;
    for(int i =0;i<G[u].size();++i){
        int v =G[u][i];
        if(vis[v]) continue;
        cnt[v]--;
        if(cnt[v]<=(G[v].size()+1)/2){
            if(v==Q) return;
            dfs(v);
        }
    }
}

int main()
{
    int u,v,tmp;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>N>>M>>Q>>S){
        for(int i=1;i<=M;++i){
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
            cnt[u]++;
            cnt[v]++;
        }
        if(S== Q) {
            cout<<"leave"<<endl;
            continue;
        }
        dfs(S);
        if(cnt[Q]<=G[u].size()/2) cout<<"leave"<<endl;
        else cout<<"stay"<<endl;
    }
    return 0;
}

/*
4 3 4 1
2 3
2 4
1 2

5 5 1 1
3 4
1 2
2 3
1 3
2 5

4 5 3 1
1 2
1 3
2 3
2 4
3 4


10 14 1 10
1 2
1 3
1 4
2 5
3 5
4 5
5 6
5 7
5 8
5 9
6 10
7 10
8 10
9 10

*/
