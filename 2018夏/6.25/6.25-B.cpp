#include<bits/stdc++.h>
using namespace std;
const int maxn =1e3+5;
int G[maxn][maxn];
int dp1[maxn][maxn],dp2[maxn][maxn],dp3[maxn][maxn],dp4[maxn][maxn];
int N,M;

inline int max(int a, int b) {return a>b?a:b;}

int solve()
{
    int res=0;
    for(int i=1;i<=N;++i){          //1正
        for(int j=1;j<=M;++j){
            dp1[i][j] = G[i][j]+max(dp1[i-1][j],dp1[i][j-1]);
        }
    }
    for(int i=N;i>=1;--i){          //2正
        for(int j=1;j<=M;++j){
            dp2[i][j] = G[i][j] + max(dp2[i+1][j],dp2[i][j-1]);
        }
    }
    for(int i=N;i>=1;--i){          //1反
        for(int j=M;j>=1;--j){
            dp3[i][j]=G[i][j] + max(dp3[i+1][j],dp3[i][j+1]);
        }
    }
    for(int i=1;i<=N;++i){
        for(int j=M;j>=1;--j){
            dp4[i][j]= G[i][j]+max(dp4[i-1][j],dp4[i][j+1]);
        }
    }
    for(int i=2;i<N;++i){
        for(int j=2;j<M;++j){
            res = max(res,dp1[i][j-1]+dp2[i+1][j]+dp3[i][j+1]+dp4[i-1][j]);
            res = max(res,dp1[i-1][j]+dp2[i][j-1]+dp3[i+1][j]+dp4[i][j+1]);
        }
    }
    return res;
}

int main()
{
    while(~scanf("%d%d",&N,&M)){
        memset(dp1,0,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        memset(dp3,0,sizeof(dp3));
        memset(dp4,0,sizeof(dp4));
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                scanf("%d",&G[i][j]);
            }
        }
        printf("%d\n",solve());
    }
    return 0;
}