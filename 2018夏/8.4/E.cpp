#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 2e5+5;
const int INF= 0x3f3f3f3F;
const LL mod = 1e9+7;
int main()
{
    char str[maxn];
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%s",str)==1){
        LL res=0;
        LL base = 1;
        int len = strlen(str);
        for(LL i=len-1;i>=0;--i){
            res = (res+base*(str[i]-'0')%mod*(i+1)%mod)%mod;
            base = (base*10%mod+1)%mod;
            str[i]=0;
        }        
        printf("%lld\n",res);
    }
    return 0;
}