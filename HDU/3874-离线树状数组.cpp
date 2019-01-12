#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =5e4+5;
const int maxv = 1e6+5;
const int maxq = 2e5+5;
LL bit[maxn];
int a[maxn],N;
LL ans[maxq];
int pos[maxv];
inline int lowbit(int x) {return x&(-x);}

void add(int i,LL val){
    for(;i<=N;i+=lowbit(i)) bit[i]+=val;   
}

LL sum(int i){
    LL res=0;
    for(;i;i-=lowbit(i)) res+=bit[i];
    return res;
}

struct Query{
    int L,R,id;
    bool operator < (const Query & p) const{return R<p.R;}
}Q[maxq];

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,K,u,v,k;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(pos,0,sizeof(pos));
        memset(bit,0,sizeof(bit));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
        }
        scanf("%d",&M);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1);
        int la=1;
        for(int i=1;i<=N;++i){
            add(i,a[i]);
            if(pos[a[i]]) add(pos[a[i]],-a[i]);
            pos[a[i]]= i;
            while(la<=M && Q[la].R==i){
                ans[Q[la].id] =sum(Q[la].R) - sum(Q[la].L-1);
                la++;
            }
            if(la>M) break;
        }
        for(int i=1;i<=M;++i)
            printf("%lld\n",ans[i]);
    }
    return 0;
}
