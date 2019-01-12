#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 1e5+10;
LL num[100];
const LL INF = 1e18+5;

LL quick_pow(LL a, LL b)
{
    LL ans = 1;
    while(b){
        if(b&1){
            if(ans > 1.0*INF/a) return -1;          //处理方法
            ans *= a;
        }
        b >>= 1;
        if(a > 1.0*INF/a && b > 0) return -1;
        a *= a;
    }
    return ans;
}

LL getnum(LL n, int k)
{
    LL ans = pow(n, 1.0/k);
    LL tmp = quick_pow(ans, k);
    if(tmp == n)  return ans;
    if(tmp > n || tmp == -1)  ans--;
    else{
        tmp = quick_pow(ans+1, k);
        if(tmp != -1 && tmp <= n) ans++;
    }
    return ans;
}

LL cal(LL n)
{
    if(n<=3) return n;
    num[1] = n;
    int k = 1;
    for(k=2;;k++){
        LL tmp = getnum(n,k);
        if(tmp==1) break;
        num[k] = tmp-1;
    }
    for(int i=k-1;i>=1;--i){            //容斥
        for(int j=2*i;j<k;j += i){
            num[i] -= num[j];
        }
    }
    LL res=0;
    for(int i=1;i<k;++i){
        res += (LL)i*num[i];
    }
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    LL L,R;
    while(scanf("%lld %lld",&L,&R)==2){
        if(!L &&!R)break;
        LL res= cal(R) - cal(L-1);
        printf("%lld\n",res);
    }
    return 0;
}