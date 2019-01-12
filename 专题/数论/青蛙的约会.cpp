#include<iostream>
#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 4e6+5;

LL Exgcd(LL a,LL b,LL &x,LL &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }
    LL d =  Exgcd(b, a%b, x, y), temp = x;
    x = y;
    y = temp-a/b*y;
    return d;
}

int main() 
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    LL x, y, n ,m ,L;
    scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
        LL c = x-y, d,t1,t2,a = n-m;
        d =Exgcd(a,L,t1,t2);     //注意正负
        if(c%d!=0){
            printf("Impossible\n");
        }
        else{
            t1=t1*c/d;
            t2=t2*c/d;
            t1 = (t1%L +L)%L;           //正解
            printf("%lld\n",t1);
        }
    return 0;
}