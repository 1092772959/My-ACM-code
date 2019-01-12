/*
离线树状数组。把查询区间按右区间升序排序，然后把数组逐个插入，
    对于当前a[i],如果之前出现过了，则把上次出现的位置 -1，当前位置 +1.
    然后若有查询区间的右区间等于i,查询该区间，把答案保存下来。

*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int N,M;
int a[maxn];
int pos[maxn];
int block;                  //块数
int vis[maxn],bit[maxn];
int ans[maxn];
struct Query{
    int L,R,id;
}Q[maxn];
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
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        memset(bit,0,sizeof(bit));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=N;++i)
            scanf("%d",&a[i]);   
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1,cmp1);
        int cnt =1;
        for(int i=1;i<=N;++i){
            update(i,1);
            if(vis[a[i]]) update(vis[a[i]],-1);
            vis[a[i]]= i;
            while(cnt<=M && Q[cnt].R==i){
                ans[Q[cnt].id] = sum(Q[cnt].R) -sum(Q[cnt].L-1);
                cnt++;
            }
            if(cnt>M) break;
        }
        printf("Case %d:\n",cas++);
        for(int i=1;i<=M;++i){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}