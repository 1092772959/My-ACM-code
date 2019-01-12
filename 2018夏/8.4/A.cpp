#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 130;
const int INF= 0x3f3f3f3f;
int dp[maxn][maxn];

int solve(int n,int m)
{
    if(dp[n][m]!=-1) return dp[n][m];
    if(n==1||m==1) return dp[n][m]=1;
    if(n<m) return dp[n][n]=solve(n,n);
    if(n==m) return dp[n][m] = solve(n,m-1)+1;
    return dp[n][m] = solve(n,m-1)+solve(n-m,m);
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    memset(dp,-1,sizeof(dp));
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%d",&N)==1){
        printf("%d\n",solve(N,N));
    }
    return 0;
}