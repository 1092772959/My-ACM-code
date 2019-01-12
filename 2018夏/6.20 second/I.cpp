#include<bits/stdc++.h>
using namespace std;
const int maxn =40;
typedef long long ll;
ll dp[maxn][2520][50];
int a[maxn];
int dic[3000];
//template<class T>
//inline T lcm(T a,T b){return a*b/__gcd(a,b);};

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

void init()
{
    int MOD=2520,cnt=0;
    for(int i=1;i<=MOD;++i){
        if(MOD%i==0)
            dic[i]=cnt++;
    }
    memset(dp,-1,sizeof(dp));
}

ll dfs(int pos,int mod=0,int lcm = 1,bool limit=true)
{
    if (pos==-1) return mod%lcm==0;
    int id =dic[lcm];
    if(!limit && dp[pos][mod][id]!=-1) return dp[pos][mod][id];
    int up = limit?a[pos]:9;
    ll res=0;
    for(int i=0;i<=up;++i){
        if(i)
            res+=dfs(pos-1,(mod*10+i)%2520,lcm*i/gcd(lcm,i),limit && i==a[pos]);
        else
            res+=dfs(pos-1,(mod*10)%2520,lcm,limit && i==a[pos]);
    }
    if(!limit) dp[pos][mod][id] = res;
    return res;
}

ll solve(ll n)
{
    int pos=0;
    while(n){
        a[pos++]=n%10;
        n/=10;
    }
    return dfs(pos-1);
}

int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--){
        ll L,R;
        scanf("%lld%lld",&L,&R);
        printf("%lld\n",solve(R)-solve(L-1));
    }
    return 0;
}