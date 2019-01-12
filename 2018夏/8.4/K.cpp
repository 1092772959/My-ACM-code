#include<stdio.h>
#include<cstring>
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn =805;
const int INF=0x3f3f3f3f;
int G[maxn][maxn];
int dir[4][2] = {1,0,-1,0,0,1,0,-1};
int dp[maxn][maxn];
struct Node{
    int x,y,step;
};
queue<Node> Q;
int N,M;
bool check(int i,int j)
{
    if(i<1 || i>N || j<1 ||j>M) return false;
    if(G[i][j]==0) return false;
    return true;
}

void BFS()
{
    while(!Q.empty()){
        Node p = Q.front();Q.pop();
        for(int i=0;i<4;++i){
            int nx = p.x +dir[i][0];
            int ny = p.y +dir[i][1];
            if(check(nx,ny)){
                G[nx][ny]= 0;
                dp[nx][ny] = min(dp[nx][ny],p.step+1);
                Q.push((Node){nx,ny,p.step+1});
            }
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int u,v,tmp,T;
    char str[maxn];
    while(scanf("%d%d",&N,&M)==2){
        int n=N,m=M;
        for(int i=1;i<=N;++i){
            scanf("%s",str);
            for(int j=1;j<=M;++j){
                G[i][j] = str[j-1]-'0';
                if(G[i][j]==0) {
                    Q.push((Node){i,j,0});
                    dp[i][j] = 0;
                }
                else dp[i][j] = INF;
            }
        }
        BFS();
        //cout<<N<<" "<<M<<endl;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;j++){
                printf("%d ",dp[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}