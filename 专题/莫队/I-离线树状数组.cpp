#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=3e4+5,maxv=1e6+5,maxq=2e5+5;
int N,M;
int a[maxn];
int pos[maxn];
int block;                  //块数
int vis[maxv],bit[maxn];
int ans[maxq];
struct Query{
    int L,R,id;
}Q[maxq];
bool cmp1(const Query& x,const Query& y){       //根据所属块的大小排序
    return x.R<y.R;
}  

void update(int i,int val)
{
    for(;i<=N;i+=i&-i) bit[i]+=val;
}

int sum(int i)
{
    int res=0;
    for(;i;i-=i&-i) res+=bit[i];
    return res;
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    int cas=1;
    while(scanf("%d",&N)==1){
        memset(bit,0,sizeof(bit));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=N;++i)
            scanf("%d",&a[i]);
        scanf("%d",&M);   
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1,cmp1);
        int cnt =1;
        for(int i=1;i<=N;++i){
            update(i,1);
            if(vis[a[i]]) update(vis[a[i]],-1);     //把上一次出现的位置-1
            vis[a[i]]= i;
            while(cnt<=M && Q[cnt].R==i){
                ans[Q[cnt].id] = sum(Q[cnt].R) -sum(Q[cnt].L-1);
                cnt++;
            }
            if(cnt>M) break;
        }
        for(int i=1;i<=M;++i){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}