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
LL Li,Ri;
LL M[20],R[20];

inline LL count(LL k, LL m, LL x)
{ 
    return (m - k + x) / m;
}

LL CRT(int s)              
{
    LL a1,r1,a2,r2;
    LL a,b,c,x,y,d;
    a1 = M[n],r1 =R[n];
    for(int i=0;i<n;i++){
        if(s&(1<<i)){
            a2 = M[i], r2 = R[i];
            a=a1,b=a2,c=r2-r1;
            d = Exgcd(a,b,x,y);
            if(c%d!=0) return 0;
            LL t=b/d;
            x=(x*(c/d)%t+t)%t;
            r1=a1*x+r1;
            a1=a1*(a2/d);
        }
    }
    r1 = (r1%a1+a1)%a1;
    return count(r1,a1,Ri) - count(r1,a1,Li-1);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,cas=1; scanf("%d",&T);
    while(T--){
        scanf("%d %lld %lld ",&n, &Li, &Ri);
        for(int i=0;i<n;++i){
            scanf("%lld %lld ",&M[i],&R[i]);
        }
        M[n] = 7,R[n] = 0;                      //多加一个模7余0的方程

        LL ans=Ri/7-Li/7;;
        if(Li%7==0) ans++;
        
        int up = 1<<n;
        for(int i=1;i<up;++i){
            int cnt = __builtin_popcount(i);
            if(cnt&1) ans -=CRT(i);           //反过来算，奇减偶加
            else ans += CRT(i);
        }
        printf("Case #%d: %lld\n",cas++,ans);
    }
    return 0;
}

