#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+9;
const int mod=1e9+7;
#define inf 0x3f3f3f3f
int n;
vector<int> mp[30];
ll dp[1<<20];
struct Point
{
    ll a,b;
}p[23];
int getnum(int s)
{
    int ans=0;
    while(s)
    {
        if(s&1) ans++;
        s>>=1;
    }
    return ans;
}
bool judge(int sta,int i)
{
    if((sta&(1<<i))==0) return false;
    if(dp[sta^(1<<i)]==-1) return false;
    for (auto &t: mp[i])
    {
        if((sta&(1<<t))==0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d",&n)!=EOF)
    {
    int sii=0;
    for(int i=0;i<n;i++) mp[i].clear();
    for(int i=0;i<n;i++)
    {
        int si;
        scanf("%lld%lld%d",&p[i].a,&p[i].b,&si);
        for(int j=0;j<si;j++)
        {
            int x;
            scanf("%d",&x);
            mp[i].push_back(x-1);
        }
    }
    ll ans=0;
    int sta=(1<<n)-1;
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    for(int s=0;s<=sta;s++)
    {
        for(int i=0;i<n;i++)
        {
            if(judge(s,i))
            {
                dp[s]=max(dp[s],dp[s^(1<<i)]+p[i].a*getnum(s)+p[i].b);
                ans=max(ans,dp[s]);
            }
        }
    }
    printf("%lld\n",ans);
    }
    return 0;
}