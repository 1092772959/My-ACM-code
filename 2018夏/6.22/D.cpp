#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =2e5+5;
vector<int> G[maxn];
int val[maxn];
int c[maxn];
int dfn;
bool used[maxn];
struct TreeNode{
    int num1,num0;
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
    tree[index].num1 = tree[index<<1].num1 + tree[index<<1|1].num1;
    tree[index].num0 = tree[index<<1].num0 + tree[index<<1|1].num0;
}

void pushdown(int index)
{
    if(tree[index].tag!=0){
        swap(tree[index<<1].num1,tree[index<<1].num0);
        swap(tree[index<<1|1].num1,tree[index<<1|1].num0);
        tree[index<<1].tag ^=1 ;tree[index<<1|1].tag^=1;
        tree[index].tag=0;
    }
}

void build(int index,int l,int r)
{
    tree[index].tag =0;
    if(l==r){ 
        tree[index].num1  = val[l];
        tree[index].num0 =  1^tree[index].num1;
        return ;
    }
    int mid = (l+r)>>1;
    build(index<<1,l,mid);
    build(index<<1|1,mid+1,r);
    pushup(index);
}

void update(int index,int L,int R,int l,int r,int flag)      //区间LR
{
    if(l<=L && r>=R){       //完全覆盖
        tree[index].tag ^= flag;
        swap(tree[index].num1,tree[index].num0);
        return ;
    }
    pushdown(index);
    int mid = (L+R)>>1;
    if(l<=mid) update(index<<1,L,mid,l,r,flag);
    if(r>mid) update(index<<1|1,mid+1,R,l,r,flag);
    pushup(index);
}

int query(int index,int L,int R,int l,int r)           //查询
{
    int ans=0;
    if(l<=L && r>=R){
        return tree[index].num1;
    }
    pushdown(index);
    int mid = (L+R)>>1;
    if(l<=mid) ans += query(index<<1,L,mid,l,r);
    if(r>mid)  ans += query(index<<1|1,mid+1,R,l,r);
    return ans;
}

int main()
{
    int N,M,v,u;
    while(scanf("%d",&N)==1){
        init(N);
        for(int i=2;i<=N;++i){
            scanf("%d",&u);
            G[u].push_back(i);
        }
        for(int i=1;i<=N;++i)   scanf("%d",&c[i]);
        dfn = 0;
        dfs(1);
        build(1,1,N);
        char op[5];
        scanf("%d",&M);
        for(int i =0;i<M;++i){
            scanf("%s",op);
            if(op[0]=='p'){
                scanf("%d",&v);
                update(1,1,N,P[v].L,P[v].R,1);
            }
            else{
                scanf("%d",&v);
                int res =query(1,1,N,P[v].L,P[v].R);
                printf("%d\n",res);
            }
        }
    }
    return 0;
}

