#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;

LL ABS(LL a)
{
    return a>=0?a :-a;
}

LL Exgcd(LL a,LL b,LL &x,LL &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = Exgcd(b, a%b, x, y), temp = x;
    x = y;
    y = temp-a/b*y;
    return d;
}

LL gao(LL a,LL b,LL c)          //ax+by=c
{
    LL x,y;
    LL d = Exgcd(a,b,x,y);
    if(c%d)  return -1;
    LL am = a/d, bm = b/d;
    x *=c/d, y*= c/d;           //特解
    LL ans= ABS(x)+ABS(y);
    for(int i=-x/bm-1;i<=-x/bm+1;i++){
        LL X=x+bm*i;
        LL Y=y-am*i;
        if(i){
            LL tmp=ABS(X)+ABS(Y);
            if(tmp<ans) ans=tmp;
        }
    }
    for(int i=y/am-1;i<=y/am+1;i++){
        LL X=x+bm*i;
        LL Y=y-am*i;
        if(i){
            LL tmp=ABS(X)+ABS(Y);
            if(tmp<ans) ans=tmp;
        }
    }
    return ans;
}   

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    LL a,b,A,B,k;
    int T; scanf("%d",&T);
    while(T--){
        scanf("%lld %lld %lld %lld",&A, &B, &a, &b);
        LL C = ABS(A-B),c = a+b;
        LL t1 =gao(a,b,C), t2 = gao(a,c,C) ,t3 = gao(b,c,C);
        if(t1==-1 && t2==-1 && t3==-1){
            puts("-1");
            continue;
        }
        LL ans=10000000000;
        if(t1!=-1) ans = min(t1,ans);
        if(t2!=-1) ans = min(t2,ans);
        if(t3!=-1) ans = min(t3,ans);
        printf("%lld\n",ans);
    }
    return 0;
}
