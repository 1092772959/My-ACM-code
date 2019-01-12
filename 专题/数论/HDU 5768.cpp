#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
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
int n;
LL M[10],R[10];

LL gcd(LL a,LL b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

LL solve()
{
    LL a1,r1,a2,r2,lcm;
    LL a,b,c,x,y,d;
    bool flag = true;
    a1 = M[1], r1 = R[1];
    for(int i=2;i<=n;i++){
        a2 = M[i], r2 = R[i];
        a=a1,b=a2,c=r2-r1;
        d = Exgcd(a,b,x,y);
        if(c%d!=0)
           return -1;
        LL t=b/d;
        x=(x*(c/d)%t+t)%t;
        r1=a1*x+r1;
        a1=a1*(a2/d);
    }
    return r1>0 ?r1 : r1+a1;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,cas=1; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i) scanf("%lld",&M[i]);
        for(int i=1;i<=n;++i) scanf("%lld",&R[i]);
        printf("Case %d: %lld\n",cas++,solve());
    }
    return 0;
}

