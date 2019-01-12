#include<bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int INF =0x3f3f3f3f;
int G[maxn][maxn];
int N,M;
int d[maxn];
bool vis[maxn];

void init()
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    for(int i=0;i<=N;++i){
        for(int j=0;j<=N;++j){
            G[i][j]=0;
        }
    }
}

int BFS(int s,int t)
{
    queue<int> Q;
    Q.push(s);
    vis[s]=true;
    int p;
    while(!Q.empty()){
        p = Q.front();Q.pop();
        if(p==t)    return d[p];        //FIND
        for(int i =1;i<=N;++i){
            if(!vis[i] && G[p][i]==1){
                d[i]=d[p]+1;
                vis[i]= true;
                Q.push(i);
            }
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x,y;
    while(cin>>N>>M){
        init();
        for(int i=0;i<M;++i){
            cin>>x>>y;
            G[x][y]=1;
            G[y][x]=1;
        }
        if(G[1][N]==1){ //火车可直接到达
          for(int i=1;i<=N;++i){
              for(int j=1;j<=N;++j){
                  if(i==j) continue;
                  else if(G[i][j]==INF){
                      G[i][j]=1;
                  }
                  else{
                      G[i][j]=INF;
                  }
              }
          }  
        }
        cout<<BFS(1,N)<<endl;
    }
    return 0;
}