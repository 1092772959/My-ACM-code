#include<bits/stdc++.h>
using namespace std;
const int maxn = 10;
int N;
int row_cnt,col_cnt;
int row[maxn][maxn],col[maxn][maxn],clink[maxn];
bool vis[maxn];
bool path[maxn][maxn];
char G[maxn][maxn];

bool dfs(int u){
    for(int v=1;v<=col_cnt;++v){
        if(path[u][v] && !vis[v]){
            vis[v] = true;
            if(clink[v]==-1||dfs(clink[v])){
                clink[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int u;
    int res=0;
    memset(clink,-1,sizeof(clink));
    for(u=1;u<=row_cnt;++u){
        memset(vis,0,sizeof(vis));
        if(dfs(u)) res++;
    }
    return res; 
}

//#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    int M,s,t,u,v,tmp;
    char str[maxn];
    while(scanf("%d",&N)==1){
        if(!N) break;
        
        memset(str,0,sizeof(str));
        for(int i=1;i<=N;++i){
            scanf("%s",str);
            for(int j=1;j<=N;++j){
                G[i][j] = str[j-1];
            }
        }
        
        row_cnt = col_cnt = 0;
        memset(row,-1,sizeof(row));
        memset(col,-1,sizeof(col));
        memset(path,0,sizeof(path));
        //缩点
        for(int i =1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(row[i][j]==-1 && G[i][j]=='.'){          //横向缩点
                    row_cnt++;
                    for(int k=j;G[i][k]=='.' &&k<=N;++k)
                        row[i][k]=row_cnt;
                }
                if(col[i][j]==-1 && G[i][j]=='.'){          //纵向缩点
                    col_cnt++;
                    for(int k=i;G[k][j]=='.' && k<=N;++k)
                        col[k][j] = col_cnt; 
                }
            }
        }
        //建图
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(G[i][j]=='.'){
                    path[row[i][j]][col[i][j]] = true;
                }
            }
        }
        printf("%d\n",hungary());
    }
    return 0;
}

