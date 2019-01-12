#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int maxM = 1<<20;
LL cnt[maxM],res,ans[maxn];
int a[maxn],pos[maxn],block;
int K,N,M;
struct Query{
    int L,R,id;
}Q[maxn];

bool cmp(const Query & x,const Query &y){
    if(pos[x.L]==pos[y.L]) return x.R<y.R;
    return pos[x.L]<pos[y.L];
}

void update(int x,int step)
{
    if(step>0){
        res+=cnt[a[x]^K];
        cnt[a[x]]++;
    }
    else{
        cnt[a[x]]--;
        res-=cnt[a[x]^K];
    }
}

int main()
{
    a[0]=0;
    while(scanf("%d%d%d",&N,&M,&K)==3){
        block = (int)(sqrt(1.0*N+0.5));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
            a[i]=a[i-1]^a[i];
            pos[i]=i/block;
        }
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1,cmp);
        memset(cnt,0,sizeof(cnt));
        cnt[0]=1;
        int curL=0,curR=0;
        res=0;
        for(int i=1;i<=M;++i){
            while(curL>Q[i].L-1) {update(--curL,1);}    
            while(curR<Q[i].R) update(++curR,1);
            while(curL<Q[i].L-1) {update(curL++,-1);}
            while(curR>Q[i].R) update(curR--,-1);
            ans[Q[i].id] = res;
        }
        for(int i=1;i<=M;++i){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}
