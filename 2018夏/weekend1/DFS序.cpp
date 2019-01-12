#include<stdio.h>

#include<string.h>

#include<vector>

#include<algorithm>

#define maxn 400010

#define LL long long

using namespace std;

LL c[maxn];

vector<int> v[maxn];

struct node

{

    LL num,fg;

}tree[maxn<<2];

struct Node

{

    int l,r;

}E[maxn];///每个点能管的范围，即包括自己所有的子树结点

LL val[maxn];

int time;

bool vis[maxn];

void dfs(int x)

{

    E[x].l=++time;

    val[time]=c[x];///记录time点的值，方便后面提取

    vis[x]=true;

    for(int i=0;i<v[x].size();i++)

    {

        int y=v[x][i];

        if(!vis[y]) dfs(y);

    }

    E[x].r=time;

}

void pushup(int id)

{

    tree[id].num=tree[id<<1].num|tree[id<<1|1].num;

}

void pushdown(int id)

{

    if(tree[id].fg)

    {

        tree[id<<1].num=tree[id<<1|1].num=(1ll<<tree[id].fg);

        tree[id<<1].fg=tree[id<<1|1].fg=tree[id].fg;

        tree[id].fg=0;

    }

}

void build(int id,int l,int r)

{

    tree[id].fg=0;

    if(l==r)
    {

        tree[id].num=(1ll<<val[l]);///由于超过int范围所以1的后面加ll

        return;

    }

    int mid=(l+r)>>1;

    build(id<<1,l,mid);

    build(id<<1|1,mid+1,r);

    pushup(id);

}

void update(int id,int L,int R,int l,int r,LL co)

{

    if(l<=L&&r>=R)

    {

        tree[id].fg=co;

        tree[id].num=(1ll<<co);

        return;

    }

    int mid=(L+R)>>1;

    pushdown(id);

    if(l<=mid) update(id<<1,L,mid,l,r,co);

    if(r>mid) update(id<<1|1,mid+1,R,l,r,co);

    pushup(id);

}

LL ans;

void solve(int id,int L,int R,int l,int r)

{

    if(l<=L&&r>=R)

    {

        ans|=tree[id].num;

        return;

    }

    pushdown(id);

    int mid=(L+R)>>1;

    if(l<=mid) solve(id<<1,L,mid,l,r);

    if(r>mid) solve(id<<1|1,mid+1,R,l,r);

}

int main()

{

    int n,m;

    while(scanf("%d%d",&n,&m)==2)

    {

        for(int i=0;i<maxn;i++) v[i].clear();

        for(int i=1;i<=n;i++) scanf("%lld",&c[i]);

        for(int i=1;i<n;i++)

        {

            int x,y;

            scanf("%d%d",&x,&y);

            v[x].push_back(y);

            v[y].push_back(x);

        }

        memset(vis,false,sizeof(vis));

        time=0;

        dfs(1);

        build(1,1,n);

        for(int i=1;i<=m;i++){
            int d,x;
            LL co;
            scanf("%d%d",&d,&x);
            if(d==1){
                scanf("%lld",&co);
                update(1,1,n,E[x].l,E[x].r,co);
            }
            else{
                ans=0;
                solve(1,1,n,E[x].l,E[x].r);
                int sum=0;
                for(;ans;ans-=ans&(-ans)) sum++;
                printf("%d\n",sum);
            }
        }
    }
    return 0;
}
