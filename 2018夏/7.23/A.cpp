#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
struct Node{
    int L,R;
    bool operator <(const Node &rhs) const {
        if(L==rhs.L) return R<rhs.R;
        return L<rhs.L;
    }
}Q[maxn];
int res[maxn];

struct SGndoe{
    int mx,mn;
}tree[maxn<<4];

void pushup(int root){
    tree[root].mx =max(tree[root<<1].mx,tree[root<<1|1].mx);
    tree[root].mn =min(tree[root<<1].mn,tree[root<<1|1].mn);
}

void build(int root,int L,int R){
    if(L==R){
        tree[L].mx=tree[L].mn=0;
        return;
    }
    int mid =(L+R)>>1;
    build(root<<1,L,mid);
    build(root<<1|1,mid+1,R);
    pushup(root);
}

void update(int root,int L,int R,int pos,int val)
{
    if(L==R && L==pos){
        tree[root].mx =tree[root].mn= val;
        return;
    }
    int mid=(L+R)>>1;
    if(pos<=mid)
        update(root<<1,L,mid,pos,val);
    else
        update(root<<1|1,mid+1,R,pos,val);
    pushup(root);
}

int getmax(int root,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
        return tree[root].mx;
    int mid=(l+r)>>1,res=0;
    if(L<=mid)
        res=max(res,getmax(root<<1,l,mid,L,R));
    if(mid<R)
        res=max(res,getmax(root<<1|1,mid+1,r,L,R));
    return res;
}

int getmin(int root,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
        return tree[root].mn;
    int mid=(l+r)>>1,res=INF;
    if(L<=mid)
        res=min(res,getmin(root<<1,l,mid,L,R));
    if(mid<R)
        res=min(res,getmin(root<<1|1,mid+1,r,L,R));
    return res;
}

void show(int N){
    for(int i=1;i<N;++i)
        printf("%d ",getmax(1,1,N,i,i));
    printf("%d\n",getmax(1,1,N,N,N));
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N; 
    scanf("%d",&T);
    LL ans;
    while(T--){
        scanf("%lld", &N);
        if( N %3 == 0 ) ans=(LL)(N/3) *(N/2) *(N/3);
        else if( N %4 == 0 ) ans=(LL)(N/2) *(N/4) *(N/4);
        else ans=-1;
        printf("%lld\n", ans);
    }
    return 0;
}

