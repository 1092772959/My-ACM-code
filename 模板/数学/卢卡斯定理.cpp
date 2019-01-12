#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
LL Pow(LL x, LL n, LL p)
{
    LL res=1;
    while(n)
    {
        if(n&1) res=x*res%p;
        x=x*x%p;
        n>>=1;
    }
    return res;
}

LL Lucas(LL n, LL k, LL p)
{
    if(k>n-k) k=n-k;
    LL res=1;
    while(n&&k){
        LL n0=n%p, k0=k%p;
        LL a=1,b=1;
        for(LL i=n0; i>n0-k0; i--) a=a*i%p;
        for(LL i=1; i<=k0; i++) b=b*i%p;
        res = res*a*Pow(b, p-2, p)%p;
        n/=p; k/=p;
    }
    return res;
}

/////////////////////递归写法


 
LL C (LL a, LL b, LL p) {
    if (a < b) return 0;
    if (b > a - b)  b = a - b;
 
    LL up = 1, down = 1;
 
    for (LL i = 0; i < b; i++) {
        up = up * (a-i) % p;
        down = down * (i+1) % p;
    }
    return up * Pow(down, p-2, p) % p; // 逆元
}
 
LL lucas (LL a, LL b, LL p) {
    if (b == 0)
        return 1;
    return C(a%p, b%p, p) * lucas(a/p, b/p, p) % p;
}
 
