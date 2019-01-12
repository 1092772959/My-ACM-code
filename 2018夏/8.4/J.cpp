#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int N,W;
int dp[maxn];
int w[maxn],v[maxn];
void solve()
{
    for(int i=1;i<=N;++i){
        for(int j=W;j>=w[i];--j){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    printf("%d\n",dp[W]);
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    while(cin>>N>>W){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=N;++i){
            scanf("%d%d",&w[i],&v[i]);
        }
        solve();
    }
    return 0;
}