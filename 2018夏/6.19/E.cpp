// 超大背包+逆元
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =20;
const int MOD =1e9+7;
map<LL,int> dp;
int vis[maxn][7];
LL ans;
int N,X;

LL fpow(LL b, LL n)
{
    LL res=1;
    while(n){
        if(n&1) res= res*b%MOD;
        b=b*b%MOD;
        n>>=1;
    }
    return res;
}

void dfs1(int L,int R,LL cur)          //左半部分枚举
{
    if(L==R){
        dp[cur]++;
        return;
    }
    for(int i=0;i<6;++i){
        dfs1(L+1,R,cur*vis[L][i]%MOD);
    }
}

void dfs2(int L,int R,LL cur)          //右半部分枚举,统计答案
{
    if(L==R){
        LL inv = fpow(cur,MOD-2);    //当前状态所需逆元
        ans +=dp[inv*X%MOD];
        return;
    }
    for(int i=0;i<6;++i){
        dfs2(L+1,R,cur*vis[L][i]%MOD);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&X);
        for(int i=0;i<N;++i){
            for(int j=0;j<6;++j){
                scanf("%d",&vis[i][j]);
            }
        }
        dp.clear();
        ans=0;
        int lr = N/2;
        dfs1(0,lr,1);
        dfs2(lr,N,1);
        printf("%lld\n",ans);
    }
    return 0;
}
