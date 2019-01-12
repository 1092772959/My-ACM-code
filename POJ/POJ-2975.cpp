#include<stdio.h>
#include<vector>
using namespace std;
const int maxn =1e3+5;
const int INF =0x3f3f3f;
typedef long long ll;
ll a[maxn];

int main()
{
    int n;
    while(scanf("%d",&n),n){
        ll res=0;
        for(int i =0;i<n;++i){
            scanf("%lld",&a[i]);
            res^=a[i];
        }
        if(res){
            ll ans=0;
            for(int i=0;i<n;++i){
                if(a[i]> (res^a[i])) 
                    ans++;
            }
            printf("%lld\n",ans);
        }
        else{
            printf("0\n");
        }
    }
    return 0;
}