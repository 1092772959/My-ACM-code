#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long LL;
const int maxn =2e5+5;

inline LL gcd(LL a,LL b){
    return b?gcd(b,a%b):a;
}

pair<LL,LL> vz[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int n;
    while(~scanf("%d",&n)){
        LL sum =0;
        for(int i=1;i<=n;++i){
            scanf("%lld %lld",&vz[i].X, &vz[i].Y);
            sum = gcd(vz[i].X * vz[i].Y ,sum);
        }
        if(sum==1) printf("-1\n");
        else{
            LL ans = 0;
            for(int i=2;i*i<=vz[1].X;++i){
                if(ans==0 && sum%i==0){
                    ans = i;
                }
                while(vz[1].X%i==0) vz[1].X/=i;
            }
            if(ans==0 && vz[1].X>1 &&sum%vz[1].X==0) ans = vz[1].X;

            for(int i=2;i*i<=vz[1].Y;++i){
                if(ans==0 && sum%i==0){
                    ans = i;
                }
                while(vz[1].Y%i==0) vz[1].Y/=i;
            }
            if(ans==0 && vz[1].Y>1 &&sum%vz[1].Y==0) ans = vz[1].Y;
            printf("%lld\n",ans);
        }
    }
    return 0;
}

