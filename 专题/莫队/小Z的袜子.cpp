#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =5e4+5;
int pos[maxn],cnt[maxn],v[maxn];
int block;
int tot;
LL res1,res2;
LL ans1[maxn],ans2[maxn];
struct Node{
    int col,id;
}a[maxn];
struct Query{
    int L,R,id;
}Q[maxn];
bool cmp(const Query & x,const Query &y){
    if(pos[x.L]==pos[y.L]) return x.R<y.R;
    return pos[x.L]<pos[y.L];
}

LL gcd(LL a,LL b){
    if(!b) return a;
    else return gcd(b,a%b);
}

void update(int pos,int step){
    res1 -=(LL)(cnt[a[pos].col]*(cnt[a[pos].col]-1))/2;
    cnt[a[pos].col] +=step;
    res1 +=(LL)(cnt[a[pos].col]*(cnt[a[pos].col]-1))/2;
}

int main()
{
    int N,M;
    while(scanf("%d%d",&N,&M)==2){
        memset(cnt,0,sizeof(cnt));
        int block =(int)sqrt((double)N+0.5);
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i].col);
            a[i].id = i;
            pos[i] = i/block;
        }
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q,Q+M,cmp);
        res1=res2=0;
        int curL=2,curR=1;
        LL tmp;
        for(int i=1;i<=M;++i){
            while(curL > Q[i].L) update(--curL,1);
            while(curR< Q[i].R)  update(++curR,1);
            while(curL<Q[i].L)  update(curL++,-1);
            while(curR>Q[i].R)  update(curR--,-1);
            if(!res1){
                ans1[Q[i].id] = 0;
                ans2[Q[i].id] = 1;
            }
            else{
                res2 =(LL) (Q[i].R-Q[i].L+1)*(Q[i].R-Q[i].L)/2;
                tmp = gcd(res1,res2);
                ans1[Q[i].id] = res1/tmp;
                ans2[Q[i].id] = res2/tmp;
            }
        }
        for(int i=1;i<=M;++i){
            printf("%lld/%lld\n",ans1[i],ans2[i]);
        }
    }   
    return 0; 
}