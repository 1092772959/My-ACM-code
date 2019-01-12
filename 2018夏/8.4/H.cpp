#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 1e4+5;
const int INF= 0x3f3f3f3F;
double dp[105][605];
void pre()
{
    for(int i=1;i<=6;++i) dp[1][i]=(double)(1.0/6);
    for(int i=2;i<=100;++i){
        for(int j=1;j<=600;++j){
            if(j<i) dp[i][j] = 0.0;
            else{
                dp[i][j] =0;
                for(int k=max(1,j-6);k<j;++k){
                    dp[i][j] += 1.0*dp[i-1][k]/6.0;
                }   
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
    dp[0][0]=0;
    pre();
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%d%d",&N,&M)==2){
        printf("%.2f\n",100.0*dp[N][M]);
    }
    return 0;
}