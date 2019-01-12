#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int a[maxn];
int pos[maxn];
int block;                  //块数
int cnt[maxn],res;
int ans[maxn];
struct Query{
    int L,R,id;
}Q[maxn];
bool cmp1(const Query& x,const Query& y){       //根据所属块的大小排序
    if(pos[x.L] ==pos[y.L] )  return x.R<y.R;
    return x.L<y.L;
}  

void add(int pos)
{
    cnt[a[pos]]++;
    if(cnt[a[pos]]==1) res++;
}

void pop(int pos)
{
    cnt[a[pos]]--;
    if(!cnt[a[pos]]) res--;
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M;
    int cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        memset(cnt,0,sizeof(cnt));
        block = ceil(sqrt(1.0*N));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
            pos[i]= i/block;
        }   
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id =i;
        }
        sort(Q+1,Q+M+1,cmp1);
        res=0;
        int curL=1,curR=0;
        for(int i=1;i<=M;++i){
            while(curL>Q[i].L) add(--curL);
            while(curR<Q[i].R) add(++curR);
            while(curL<Q[i].L) pop(curL++);
            while(curR>Q[i].R) pop(curR--);
            ans[Q[i].id] = res;
        }
        printf("Case %d:\n",cas++);
        for(int i=1;i<=M;++i){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}