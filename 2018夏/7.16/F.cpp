#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e3+5;
const int mod = 7901;
int a[maxn];

//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int T,N;
    scanf("%d",&T);
    while(T--){
        LL res=1,cnt=1;
        scanf("%d",&N);
        for(int i=1;i<=N;++i) scanf("%d",&a[i]);
        sort(a+1,a+N+1);
        for(int i=2;i<=N;++i){
            if(a[i]==a[i-1]){
                ++cnt;
                res = (res*cnt)%mod;
            }
            else
                cnt=1;
        }
        printf("%lld\n",res);
    }    
    return 0;
}