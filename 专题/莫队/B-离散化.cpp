#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
struct Node{
    int val,id;
    bool operator < (const Node &p) const {return val<p.val;}
}a[maxn];
bool cmpid (const Node &p1, const Node &p2) {return p1.id<p2.id;}
int pos[maxn];
int block;                  //块数
ll cnt[maxn],ans;
ll res[maxn];
int v[maxn];
struct Query{
    int L,R,id;
}Q[maxn];

bool cmp1(const Query& x,const Query& y){       //根据所属块的大小排序
    if(pos[x.L] ==pos[y.L] )  return x.R<y.R;
    return x.L<y.L;
}  

void update(int pos,int step)
{
    int id = v[a[pos].id];
    ans -=cnt[id]*cnt[id]*cnt[id];
    cnt[id] = cnt[id] +step;
    ans +=cnt[id]*cnt[id]*cnt[id];
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,q;
    while(scanf("%d",&N)==1){
        memset(cnt,0,sizeof(cnt));
        block = ceil(sqrt(1.0*N));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i].val);
            a[i].id = i;
            pos[i]=i/block;
        }
        //离散化
        sort(a+1,a+N+1);
        int tag=1;
        v[a[1].id]  = tag; 
        for(int i=2;i<=N;++i){
            if(a[i].val!=a[i-1].val) v[a[i].id]  = ++tag;
            else v[a[i].id] = tag;
        }
        sort(a+1,a+N+1,cmpid);
        
        scanf("%d",&q);
        for(int i=0;i<q;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id=i;
        }

        sort(Q,Q+q,cmp1);               //查询排序
        int curL=1,curR=0;
        ans=0;
        for(int i =0;i<q;++i){
            while(curL>Q[i].L)  update(--curL,1);
            while(curR<Q[i].R)  update(++curR,1);
            while(curL<Q[i].L)  update(curL++,-1);
            while(curR>Q[i].R)  update(curR--,-1);
            res[Q[i].id]=ans;
        }
        for(int i=0;i<q;++i){
            printf("%I64d\n",res[i]);
        }
    }
    return 0;
}