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

LL slove()              //不互素
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
    else  return r1>0 ? r1:r1+a1;       //非零结果
}
//x==r1(mod a1)
//x==r2(mod a2).....

//互素的情况
LL M[10],R[10];
LL solve()
{
    LL a1,r1,a2,r2,lcm;
    LL a,b,c,x,y,d;
    LL MOD=1;
    for(int i=0;i<n;++i){
        MOD *= M[i];
    }
    LL ans=0;
    for(int i=0;i<n+1;++i){
        LL mi = MOD / M[i];
        Exgcd(mi,M[i],x,y);
        x = (x%M[i]+M[i]) %M[i];
        ans +=(R[i]*mi*x) %MOD;      
        ans = (ans % MOD + MOD) % MOD;
    }    
    return ans;
}

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
