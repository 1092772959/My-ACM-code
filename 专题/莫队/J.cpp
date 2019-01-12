#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =2e5+5;
const int maxv = 1e6+5;
int block;
int a[maxn];
int cnt[maxv];
int pos[maxn];
LL ans[maxn],res;
struct Query{
    int L,R,id;
    bool operator <(const Query &p) {
        if(pos[L]==pos[p.L]) return R<p.R;
        return pos[L]<pos[p.L];
    }
}Q[maxn];

void add(int pos)
{
    res+= (LL)(cnt[a[pos]]*2+1)*a[pos];
    cnt[a[pos]]++;
}

void del(int pos)
{
    cnt[a[pos]]--;
    res-= (LL)(cnt[a[pos]]*2+1)*a[pos];
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M,K,u,v,k;
    while(scanf("%d%d",&N,&M)==2){
        block = ceil(sqrt(1.0*N));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
            pos[i]= i /block;
        }
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1);
        res=0;
        int curL=0,curR=0;
        for(int i=1;i<=M;++i){
            while(curL>Q[i].L)  add(--curL);
            while(curR<Q[i].R)  add(++curR);
            while(curL<Q[i].L)  del(curL++);
            while(curR>Q[i].R)  del(curR--);
            ans[Q[i].id]= res;
        }
        for(int i=1;i<=M;++i)
            printf("%lld\n",ans[i]);
    }
    return 0;
}
