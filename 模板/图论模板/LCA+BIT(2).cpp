#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5+5;
struct Edge {
    int id, v, w, next;
}edge[MAX_N << 1];
int W[MAX_N];
int bit[MAX_N << 1];                //树状数组
int tot, head[MAX_N];
int dfn,index, dfs_seq[MAX_N << 1],pos[MAX_N]; //dfs序列
int First[MAX_N], End[MAX_N]; //First数组表示第一次遍历到的时间戳，End数组表示最后回溯时遍历到的时间戳
int dep[MAX_N << 1]; //深度
int N, Q, st;
int dp[MAX_N<<1][20]; //dp[i][j]表示从时间戳i开始，长度为(1 << j)的区间中深度最小的点的时间戳
int G[MAX_N];

void Init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    index= dfn=0;
    memset(bit, 0, sizeof(bit));
}
 
void Insert(int u, int v, int w,int id)
{
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].id = id;
    edge[tot].next = head[u];
    head[u] = tot++;
}
 
int lowbit(int x)
{
    return x & (-x);
}
void update(int i, int val)
{
    while (i < index) {
        bit[i] += val;
        i += lowbit(i);
    }
}

int getSum(int i)
{
    int sum = 0;
    while (i > 0){
        sum += bit[i];
        i -= lowbit(i);
    }
    return sum;
}

void dfs(int u, int fa, int d)
{
    First[u] = ++dfn;
    dfs_seq[index] = u;
    dep[index] = d;
    pos[u]=index++;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].v, w = edge[i].w;
        if (v == fa) continue;
        G[edge[i].id] = v;                  //
        dfs(v, u, d + 1);
        dfs_seq[index] = u;
        dep[index++] = d;
    }
    End[u] = dfn;
}

void Init_RMQ(int n)
{
    for (int i = 1; i <= n; ++i) dp[i][0] = i;
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            dp[i][j] = (dep[ dp[i][j - 1] ] < dep[ dp[i + (1 << (j - 1))][j - 1] ] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}
 
 int RMQ_Query(int l, int r)
 {
     int k = (int)(log(r * 1.0 - l + 1) / log(2.0));
     return (dep[ dp[l][k] ] < dep[ dp[r - (1 << k) + 1][k] ] ? dp[l][k] : dp[r - (1 << k) + 1][k]);
 }
 
int LCA(int x, int y)
{
     x = pos[x],y=pos[y];
     if (x > y) swap(x, y);
     return dfs_seq[RMQ_Query(x, y)];
}

int main()
{
    while (~scanf("%d %d %d", &N, &Q, &st)) {
        Init();
        for (int i = 1; i < N; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            Insert(u, v, w,i);
            Insert(v, u, w,i);
            W[i] = w;
        }

        dfs(1,-1, 0);
        Init_RMQ(2*N-1);

        for(int i=1;i<N;++i){
            update(First[G[i]],W[i]);
            update(End[G[i]]+1,-W[i]);
        }

        for (int i = 1; i <= Q; ++i) {
            int opt;
            scanf("%d", &opt);
            if (!opt) {
                int ed, fa, x, y, z;
                scanf("%d", &ed);
                x = First[st], y = First[ed], z = First[LCA(st, ed)];
                printf("%d\n", getSum(x) + getSum(y) - 2 * getSum(z));
                st = ed;
            }
            else{
                int tmp,id, w;
                scanf("%d %d", &id, &w);
                tmp = w-W[id];
                update(First[G[id]],tmp);
                update(End[G[id]]+1,-tmp);
                W[id]=w;
            }
        }
    }
    return 0;
}
