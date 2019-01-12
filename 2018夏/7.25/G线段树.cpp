#include<bits/stdc++.h>
#define Lson rt<<1,l,m
#define Rson rt<<1|1,m+1,r
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
struct Node{
    int cnt,addv,maxa,minb;
}tree[maxn<<2];
int b[maxn];
void pushup(int rt)
{
    tree[rt].cnt = tree[rt<<1].cnt+tree[rt<<1|1].cnt;
    tree[rt].maxa = max(tree[rt<<1].maxa,tree[rt<<1|1].maxa);
    tree[rt].minb = min(tree[rt<<1].minb,tree[rt<<1|1].minb);
}
void pushdown(int rt)
{
    if(tree[rt].addv){
        int v=tree[rt].addv;
        tree[rt].addv=0;
        tree[rt<<1].maxa+=v;
        tree[rt<<1|1].maxa+=v;
        tree[rt<<1].addv+=v;
        tree[rt<<1|1].addv+=v;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].addv=0;
    if(l==r){
        tree[rt].cnt = tree[rt].maxa = 0;
        tree[rt].minb = b[l];
        return;
    }
    int m = (l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}
void update(int rt,int l,int r,int L,int R)
{
    if(L<=l && R>=r){
        tree[rt].maxa++;
        if(tree[rt].maxa<tree[rt].minb){    //还没有元素做出贡献
            tree[rt].addv++;
            return;
        }
        else if(l==r){
            tree[rt].cnt++;
            tree[rt].minb+=b[l];
            return;
        }
    }
    pushdown(rt);
    int m = (l+r)>>1;
    if(L<=m)update(Lson,L,R);
    if(R>m)update(Rson,L,R);
    pushup(rt);
}

int query(int rt,int l,int r,int L,int R)
{
    if(L<=l&&R>=r) return tree[rt].cnt;
    int m =(l+r)>>1;
    pushdown(rt);
    int ans=0;
    if(L<=m) ans+=query(Lson,L,R);
    if(R>m) ans+=query(Rson,L,R);
    return ans;
}  

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        for(int i=1;i<=N;++i)  scanf("%d",&b[i]);
        build(1,1,N);
        char op[8];
        int L,R;
        while(M--){
            scanf("%s %d %d",op,&L,&R);
            if(op[0]=='a') update(1,1,N,L,R);
            else printf("%d\n",query(1,1,N,L,R));
        }
    }
    return 0;
}
