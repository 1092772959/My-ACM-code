#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 2e5+5;
typedef long long LL;
LL fac[maxn],inv[maxn];
LL res[maxn];

LL qpow(LL b,int n){
    LL res=1;
    while(n){
        if(n&1) res=res*b%mod;
        b = b*b%mod;
        n>>=1;
    }
    return res;
}

void pre()
{
    fac[0]=fac[1]=1;
    for(int i=2;i<maxn;++i) fac[i]=i*fac[i-1]%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for(int i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

LL Comb(int n,int k) {  
    if(n==k) return 1;
    else if(n<k) return 0;
    return fac[n]*inv[k]%mod *inv[n-k]%mod;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T; scanf("%d",&T);
    while(T--){
        int N,M,k; scanf("%d%d%d",&N,&M,&k);
        if(k<=N-1){
            printf("%lld\n",Comb(M+k-1,k));
        }   
        else if(k>M*(N-1)){
            printf("0\n");
        }
        else{
            LL res=0;
            for(int i=0;i<=k/N;++i){
                if(i&1){
                    res = (res+mod-Comb(M,i)*Comb(M+k-1-i*N,k-i*N)%mod)%mod;
                }
                else{
                    res = (res+Comb(M,i)*Comb(M+k-1-i*N,k-i*N)%mod)%mod;
                }
            }
            printf("%lld\n",res);
        }
    }
    return 0;    
}