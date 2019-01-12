#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll s,g;

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

int main()
{
    while(scanf("%lld%lld",&s,&g)==2){
        ll res;
        if(gcd(g,s-g)==g && s!=g)  res=g;
        else res=-1;
        if(res<0)    printf("%d\n",-1);
        else printf("%lld %lld\n",res,s-res);
    }
    return 0;
}