#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
LL val[maxn];
struct TreeNode{
    LL num;
    int tag;
}tree[maxn<<2];

void pushup(int rt){ tree[rt].num = tree[lson].num + tree[rson].num;}

void pushdown(int l,int r,int rt){
    if(tree[rt].tag!=0){
        tree[lson].tag +=tree[rt].tag;
        tree[rson].tag +=tree[rt].tag;
        int m = (l+r)>>1;
        tree[lson].num += (m-l+1)*tree[rt].tag;
        tree[rson].num += (r-m)*tree[rt].tag;
        tree[rt].tag =0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].tag =0;
    if(l==r){ 
        tree[rt].num = val[l];
        return ;
    }
    int m = (l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int L,int R,LL v,int l,int r,int rt)      //区间LR
{
    if(L<=l && R>=r){       //完全覆盖
        tree[rt].tag += v;
        tree[rt].num += v*(r-l+1);
        return ;
    }
    pushdown(l,r,rt);
    int m = (l+r)>>1;
    if(L<=m) update(L,R,v,Lson);
    if(R>m) update(L,R,v,Rson);
    pushup(rt);
}

LL query(int L,int R,int l,int r,int rt)           //查询
{
    LL ans=0;
    if(L<=l && R>=r) return tree[rt].num;
    pushdown(l,r,rt);
    int m = (l+r)>>1;
    if(L<=m) ans+= query(L,R,Lson);
    if(R>m)  ans+= query(L,R,Rson);
    return ans;
}


int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,k;
    int op;
    while(scanf("%d%d",&N,&M)==2){
        for(int i=1;i<=N;++i) scanf("%lld",&val[i]);
        build(1,N,1);
        int l,r;
        while(M--){
            scanf("%d%d%d",&op,&l,&r);
            if(op==1){
                LL v;
                scanf("%lld",&v);
                update(l,r,v,1,N,1);
            }
            else{
                printf("%lld\n",query(l,r,1,N,1));
            }
        }
    }
    return 0;
}