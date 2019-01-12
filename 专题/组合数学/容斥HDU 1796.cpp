#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL a,LL b){
    if(b==0) return a;
    return gcd(b,a%b);
}

LL lcm(LL a,LL b){
    return a/gcd(a,b)*b;
}

LL vz[20];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    LL N,M;
    while(scanf("%lld %lld",&N,&M)==2){
        N--;
        int tot=0;
        for(int i=0;i<M;++i){
            LL tmp; scanf("%lld",&tmp);
            if(!tmp) continue;              //0无效
            vz[tot++] = tmp;
        }
        LL ans = 0;
        M = tot;
        for(int i =1;i<(1<<M);++i){
            LL cnt = 0, lc = 1;
            for(int j=0; j<M ;++j){
                if(i&(1<<j)){
                    cnt++;
                    lc = lcm(lc,vz[j]);
                }
            }
            if(cnt&1) ans +=N/lc;
            else ans -=N/lc;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
