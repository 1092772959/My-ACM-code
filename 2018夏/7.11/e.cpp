#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int INF = 2e9 + 10;
ll gcd(ll a,ll b)      //gcd
{
    if(b==0) return a;
    return gcd(b,a%b);
}

ll qpow(ll a,ll b, ll mod)
{
    ll res=1;
    if(!a) return 0;
    while(b)
    {
        if(b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}

ll euler(ll n)      //欧拉函数
{
    ll ans=n;
    for(ll i=2;i*i<=n;++i)
    {
        if(n%i==0){
         ans = ans/i*(i-1);
         for(;n%i==0;n/=i);
        }
    }
    if(n!=1) ans=ans/n*(n-1);
    return ans;
}

int solve(int n, int m)
{
    if( m == 1) return 0;
    if( m < 0)
    {
        if( n >= 5) return INF;
        if( n == 4 ) return 262144;
        if( n == 3 ) return 9;
        if( n == 2 ) return 2;
        if( n == 1 ) return 1;
    }
    if( n == 1) return 1;

    int phi = euler(m);
    int comp = solve(n-1, -1);
    if( gcd(n, m) == 1) return qpow(n, solve(n-1, phi), m);
    else if( comp < phi) return qpow(n, comp, m);
    else return (ll)qpow(n, solve(n-1, phi), m)* qpow(n, phi, m) %m;
}
int main()
{
    ll n,m;
    while(cin>>n>>m)
        cout<<solve(n,m)<<endl;
    return 0;
}
