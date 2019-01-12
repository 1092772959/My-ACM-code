#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int MOD =1e9+7;
LL a[maxn];
LL L[maxn],R[maxn];

int main()
{
    int T,N;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        LL sum=1;
        for(int i=1;i<=N;++i){
            scanf("%lld",&a[i]);
            sum=(sum*a[i])%MOD;
        }
        sum=(sum*N)%MOD;
        L[0]=R[N+1]=1;
        for(int i=1;i<=N;++i){
            L[i]=(L[i-1]*a[i])%MOD;
        }
        for(int i=N;i>=1;--i){
            R[i]=(R[i+1]*a[i])%MOD;
        }
        LL tmp;
        for(int i=1;i<=N;++i){
            tmp = (L[i-1]*R[i+1])%MOD;
            sum = (sum+MOD-tmp)%MOD;
        }
        printf("%lld\n",sum);
    }
    return 0;
}