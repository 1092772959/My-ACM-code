#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int sz[N];
int fa[N];

//权值线段树——————数据结构
struct Tree{
  int l,r;
  int sum;      //记录 值对应为该结点下标的物品的个数
}t[N<<2];

void push_up(int index)
{
    t[index].sum = t[index<<1].sum + t[index<<1|1].sum;
}

void build(int l,int r,int index)
{
    t[index].l = l,t[index].r = r;
    t[index].sum = 0;
    if(l == r)  return;
    int mid = (l + r)>>1;
    build(l,mid, index <<1);
    build(mid + 1,r, index <<1|1);
}

void update(int x,int val,int index)
{
    if(t[index].l == t[index].r){
        t[index].sum += val;
        return;
    }
    int mid = (t[index].l + t[index].r)>>1;
    if(x <= mid)    update(x,val,index<<1);
    else    update(x,val,index<<1|1);
    push_up(index);
}

int query(int k,int index)
{
    if(t[index].l == t[index].r)   return t[index].l;
    if(t[index<<1|1].sum >= k)  return query(k,index<<1|1);
    else return query(k - t[index<<1|1].sum,index<<1);
}

void init(int n)
{
    for(int i = 1;i <= n;i ++)
        sz[i] = 1,fa[i] = i;
    build(1,n,1);
    update(1,n,1);
}

int Find(int x)
{
  if(fa[x] != x)
    fa[x] = Find(fa[x]);
  return fa[x];
}

void Merge(int a,int b)
{
    a = Find(a),b = Find(b);
    if(fa[a] != fa[b]){
        update(sz[fa[a]],-1,1);
        update(sz[fa[b]],-1,1);
        sz[fa[b]] += sz[fa[a]];
        fa[a] = fa[b];
        update(sz[fa[b]],1,1);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m,op,a,b,k;
        scanf("%d%d",&n,&m);
        init(n);
        for(int i = 0;i < m;i ++){
            scanf("%d",&op);
            if(!op){
                scanf("%d%d",&a,&b);
                Merge(a,b);
            }
            else{
                scanf("%d",&k);
                printf("%d\n",query(k,1));
            }
        }
    }
    return 0;
}
