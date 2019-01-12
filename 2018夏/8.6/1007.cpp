#include<bits/stdc++.h>
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson l, m, lson
#define Rson m + 1, r, rson
using namespace std;
typedef long long LL;
typedef unsigned int UI;
const int MOD = 1<<30;
const int maxn = 1e5+5;
UI X,Y,Z;

LL mn[maxn<<2];
void pushup(int rt) { mn[rt] = min(mn[lson],mn[rson]);}

void build(int l,int r,int rt)
{
    if(l==r) {
        mn[rt]=0;
        return;
    }
    int m =(l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int L,int R,int l,int r,int rt,LL val)
{
    if(mn[rt]>=val) return;
    if(l==r){
        mn[rt] = val;
        return ;
    }
    int m =(l+r)>>1;
    if(L<=m) update(L,R,Lson,val);
    if(R>m) update(L,R,Rson,val);
    pushup(rt);
}

LL query(int p,int l,int r,int rt)
{
    if(l == r) return mn[rt];
    int m = (l+r)>>1;
    if(p<=m) return query(p,Lson);
    else return query(p,Rson);
}

UI gao()
{
    X = X^(X<<11);
    X = X^(X>>4);
    X = X^(X<<5);
    X = X^(X>>14);
    UI W = X^(Y^Z);
    X = Y;
    Y = Z;
    Z = W;
    return Z;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    UI N,M;
    scanf("%d",&T);
    while(T--){
        scanf("%u%u%u%u%u",&N,&M,&X,&Y,&Z);
        build(1,N,1);
        int l,r,v;
        for(int i=0;i<M;++i){
            l = gao()%N +1;
            r = gao()%N +1;
            v = gao()%MOD;
            if(l>r) swap(l,r);
            update(l,r,1,N,1,v);
        }
        LL ans=0;
        for(int i=1;i<=N;++i)  ans ^= i*query(i,1,N,1);
        printf("%lld\n",ans);
    }    
    return 0;
}