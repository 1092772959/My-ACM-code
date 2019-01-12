#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e6+5;
vector<int> G[maxn];
int val[maxn];
int c[maxn];
int dfn;
bool used[maxn];
struct TreeNode{
    LL num;
    int tag;
}tree[maxn<<2];

struct Range{
    int L,R;
}P[maxn];

void dfs(int u)
{
    used[u]=true;
    int v;
    P[u].L = ++dfn;
    val[dfn] = c[u];
    for(int i=0;i<G[u].size();++i){
        v =G[u][i];
        if(!used[v])
            dfs(v);
    }
    P[u].R=dfn;
}

void init(int n)
{
    memset(used,0,sizeof(used));
    for(int i=0;i<=n;++i){
        G[i].clear();
    }
}

void pushup(int index)
{
    tree[index].num = tree[index<<1].num | tree[index<<1|1].num;
}

void pushdown(int index)
{
    if(tree[index].tag!=0){
        tree[index<<1].num = tree[index<<1|1].num =((LL)1<< tree[index].tag);
        tree[index<<1].tag = tree[index<<1|1].tag = tree[index].tag;
        tree[index].tag=0;
    }
}

void build(int index,int l,int r)
{
    tree[index].tag =0;
    if(l==r){ 
        tree[index].num  = ((LL)1<<val[l]);
        return ;
    }
    int mid = (l+r)>>1;
    build(index<<1,l,mid);
    build(index<<1|1,mid+1,r);
    pushup(index);
}

void update(int index,int L,int R,int l,int r,int col)      //区间LR
{
    if(l<=L && r>=R){       //完全覆盖
        tree[index].tag = col;
        tree[index].num = ((LL)1<<col);
        return ;
    }
    pushdown(index);
    int mid = (L+R)>>1;
    if(l<=mid) update(index<<1,L,mid,l,r,col);
    if(r>mid) update(index<<1|1,mid+1,R,l,r,col);
    pushup(index);
}

LL query(int index,int L,int R,int l,int r)           //查询
{
    LL ans=0;
    if(l<=L && r>=R){
        return tree[index].num;
    }
    pushdown(index);
    int mid = (L+R)>>1;
    if(l<=mid) ans|= query(index<<1,L,mid,l,r);
    if(r>mid)  ans|= query(index<<1|1,mid+1,R,l,r);
    return ans;
}


int main()
{
    int N,M,v,u,op,col;
    while(scanf("%d%d",&N,&M)==2){
        init(N);
        for(int i=1;i<=N;++i)   scanf("%d",&c[i]);
        for(int i=1;i<N;++i){
            scanf("%d%d",&v,&u);
            G[v].push_back(u);
            G[u].push_back(v);
        }
        dfn = 0;
        dfs(1);
        build(1,1,N);
        for(int i =0;i<M;++i){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d",&v,&col);
                update(1,1,N,P[v].L,P[v].R,col);
            }
            else{
                scanf("%d",&v);
                LL res =query(1,1,N,P[v].L,P[v].R);
                int cnt=0;
                for(;res;res-=res&(-res)) cnt++;
                printf("%d\n",cnt);
            }
        }
    }
    return 0;
}
/*
10 10
59 59 59 59 59 59 59 59 59 59
6 8
6 10
2 6
2 5
7 2
10 1
4 2
7 3
9 1
1 8 59
2 8
1 3 59
1 4 59
1 8 59
1 2 59
1 5 59
1 10 59
2 2
2 5
*/