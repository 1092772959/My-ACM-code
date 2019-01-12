#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
typedef long long LL;
const LL mod = 998244353;
LL res[maxn];

void pre()
{
    res[0] =1;
    res[1] = 0;
    res[2] = 0;
    res[3] = 1;
    res[4] = 1;
    for(int i=5;i<maxn;++i){
        if(i&1)
            res[i] = ( (i-2)*res[i-1] %mod +(i-1)*res[i-2]%mod + 1)  %mod;
        else
            res[i] = ( (i-2)*res[i-1] %mod +(i-1)*res[i-2]%mod +mod -1)  %mod;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T; scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        printf("%lld\n",res[n]);
    }
    return 0;
}