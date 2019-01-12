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
LL slove()
{
    LL a1,r1,a2,r2;
    LL a,b,c,x,y,d;
    bool flag = true;
    scanf("%lld%lld",&a1,&r1);
    for(int i=1;i<n;i++){
        scanf("%lld %lld",&a2,&r2);
        if(!flag) continue;
        a=a1,b=a2,c=r2-r1;
        d = Exgcd(a,b,x,y);
        if(c%d!=0)
           flag=false;
        LL t=b/d;
        x=(x*(c/d)%t+t)%t;
        r1=a1*x+r1;
        a1=a1*(a2/d);
    }
    if(!flag)  return -1;
    else  return r1%a1;
}

//x==r1(mod a1)
//x==r2(mod a2).....
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d",&n)==1){
        LL t=slove();
        printf("%lld\n",t);
    }
    return 0;
}
