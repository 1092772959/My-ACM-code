#include<iostream>
#include<map>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
typedef long long LL;
const int MAXN = 1e3 +10;
const LL MOD = (LL)1 << 62;

int N , M;

LL qpow( LL base , LL index)
{
    LL ans = 1;
    base %= MOD;
    while( index)
    {
        if( index&1)
            ans = ans *base % MOD;
        index/=2;
        base = base *base % MOD;
    }
    return ans;
}
LL gcd(LL a, LL b)
{
    return b==0 ? a : gcd(b,a%b);
}

LL rot()
{
    LL ans = 0;
    for(int i=1 ; i<= N ; i++)
        ans= (ans +qpow(M , gcd(i, N )) ) %MOD;
    return ans;
}

LL turn()
{
    LL ans = 0;
    if( N & 1 )
        ans += N *qpow(M,(N + 1)/2 ) %MOD;
    else
        ans = (ans + N/2 * qpow(M ,N /2)+N/2 * qpow(M, N/2+1) )%MOD;
    return ans;
}

LL polya()
{
    if(!N) return 0;
    LL ans = rot() + turn();
    ans /= 2* N;
    return ans;
}

int main()
{
    M=3;
    while(cin>>N && N!=-1){       //m种颜色，n个项链
        printf("%lld\n",polya());
    }
    return 0;
}
