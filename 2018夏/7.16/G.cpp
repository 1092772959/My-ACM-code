#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
LL a[maxn];

LL gcd(LL a,LL b){
    if(!b) return a;
    return gcd(b,a%b);
}

LL lcm(LL a,LL b)    {return a*b/gcd(a,b);}

#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int T,N;
    LL X,Y;
    scanf("%d",&T);
    while(T--){
        scanf("%d%lld%lld",&N,&X,&Y);
        for(int i=1;i<=N;++i){
            scanf("%lld",&a[i]);
        }
        if(Y%X || (N==1 && X!=Y)){
            printf("-1\n");
            continue;
        }

        int res=0;
        LL __gcd=-1,__lcm=-1;
        for(int i=1;i<=N;++i){
            if(a[i]%X || Y%a[i]){
                res++;
                a[i]=X;
            }
        
            if(__lcm==-1) __lcm = a[i];
            else __lcm = lcm(__lcm,a[i]);
            if(__gcd==-1) __gcd = a[i];
            else __gcd = gcd(__gcd,a[i]);
            
        }
        int ans=0;
        if(__gcd!=X) ans++;
        if(__lcm!=Y) ans++;
        printf("%d\n",max(res,ans));
    }
    return 0;
}
