#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int mod = 1e9+7;
LL fac[maxn],inv[maxn];
LL rev2;
LL qpow(LL b,int n){
    LL res=1;
    while(n){
        if(n&1) res=res*b%mod;
        b = b*b%mod;
        n>>=1;
    }
    return res;
}

LL Comb(int n,int k)
{
    return fac[n]*inv[k]%mod *inv[n-k]%mod;
}

void pre()
{
    rev2 = qpow(2,mod-2);
    fac[0]=fac[1]=1;
    for(int i=2;i<maxn;++i) fac[i]=i*fac[i-1]%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for(int i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

int pos[maxn];

struct Query{
    int L,R,id;
    bool operator <(const Query& p) const{
        if(pos[L]==pos[p.L]) return R<p.R;
        return L<p.L;                           //N大的排前面
    } 
}Q[maxn];
LL res;
LL ans[maxn];

inline void addN(int posL,int posR)
{
    res = (2*res%mod - Comb(posL-1,posR)+mod)%mod;
}

inline void addM(int posL,int posR)
{
    res = (res+Comb(posL,posR))%mod;
}

inline void delN(int posL,int posR)
{
    res = (res+Comb(posL-1,posR))%mod *rev2 %mod;
}

inline void delM(int posL,int posR)
{
    res = (res-Comb(posL,posR)+mod)%mod;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp,K;
    int a,b;
    pre();
    int block = (int)sqrt(1.0*maxn);
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        scanf("%d%d",&Q[i].L,&Q[i].R);
        pos[i] = i/block;
        Q[i].id = i;
    }
    sort(Q+1,Q+T+1);
    res=2;
    int curL=1,curR=1;
    for(int i=1;i<=T;++i){
        while(curL<Q[i].L) addN(++curL,curR);           //ok
        while(curR<Q[i].R) addM(curL,++curR);           //ok
        while(curL>Q[i].L) delN(curL--,curR);           //ok
        while(curR>Q[i].R) delM(curL,curR--);           //ok
        ans[Q[i].id] = res;
    }
    for(int i=1;i<=T;++i) printf("%lld\n",ans[i]);
    return 0;
}
