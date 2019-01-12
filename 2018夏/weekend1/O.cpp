#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn =1e5+5;
ll a;
int n;

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    else return gcd(b,a%b); 
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ll res=1;
        for(int i=0;i<n;++i){
            scanf("%lld",&a);
            res = res*a/gcd(res,a);
        }
        printf("%lld\n",res);
    }
    return 0;
}

