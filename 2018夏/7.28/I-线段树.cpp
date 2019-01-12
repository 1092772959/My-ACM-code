#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int INF =0x3f3f3f3f;
const int maxv = 1e6+5;
typedef long long LL;
struct SGndoe{
    LL sum;
    LL mx;
}tree[maxn<<4];
LL a[maxn];
LL ans[maxv];

void pre()
{
    for(int i=1;i<=1e6;++i){
        for(int j=0;j<=1e6;j+=i){
            ans[j]++;
        }
    }
}

void pushup(int root)
{
    tree[root].sum =tree[root<<1].sum+tree[root<<1|1].sum;
    tree[root].mx = max(tree[root<<1].mx,tree[root<<1|1].mx);
}

void build(int root,int L,int R){
    if(L==R){
        tree[root].sum = tree[root].mx=a[L];
        return;
    }
    int mid =(L+R)>>1;
    build(root<<1,L,mid);
    build(root<<1|1,mid+1,R);
    pushup(root);
}

void update(int root,int l,int r,int L,int R)
{
    if(L<=l && R>=r && tree[root].mx<=2) return;
    else if(l==r){
        tree[root].sum = ans[tree[root].sum];
        tree[root].mx = tree[root].sum;
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid)update(root<<1,l,mid,L,R);
    if(R>mid) update(root<<1|1,mid+1,r,L,R);
    pushup(root);
}

LL query(int root,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return tree[root].sum;
    int mid=(l+r)>>1;
    LL res=0;
    if(L<=mid) res+=query(root<<1,l,mid,L,R);
    if(mid<R) res+=query(root<<1|1,mid+1,r,L,R);
    return res;
}

int main(){
    int T,N,M,num,t,x;
    int L,R;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int cas=1;
    while(scanf("%d%d",&N,&M)==2){
        for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
        build(1,1,N);
        int op;
        for(int i=1;i<=M;++i){
            scanf("%d%d%d",&op,&L,&R);
            if(op==1) update(1,1,N,L,R);
            else printf("%lld\n",query(1,1,N,L,R));
        }
    }
    return 0;
}