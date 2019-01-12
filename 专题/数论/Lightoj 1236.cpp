#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e7+5;
const int INF =0x3f3f3f3f;

bool notprime[maxn<<1];
vector<int> prime;
  //prime[0] 表示当前范围内有多少素数,prime[i] 表示第i个素数是多少
void pre()
{
    memset(notprime,0,sizeof(notprime));
    notprime[0] = notprime[1] = true;
    for(int i=2;i<maxn;++i){
        if(!notprime[i]) prime.push_back(i);
        for(int j=0 ; j<prime.size() && prime[j] <= maxn / i ;++j){
            notprime[prime[j]*i] = true;
            if(i%prime[j]==0) break;
        }
    }
}

LL getFactor(LL n)
{
    LL tmp = n , res=1;
    for(int i=0;i<prime.size() && prime[i]*prime[i]<=tmp;++i){
        int cnt =0;
        while(tmp%prime[i]==0){
            cnt++;
            tmp/=prime[i];
        }
        res *=(2*cnt +1 );
    }
    if(tmp>1) res*= 3;   
    res++;
    res>>=1;
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T,N,u,v,tmp,cas=1;
    scanf("%d",&T);
    while(T--){
        LL n; scanf("%lld",&n);
        LL res= getFactor(n);
        printf("Case %d: %lld\n",cas++,res);
    }
    return 0;
}
