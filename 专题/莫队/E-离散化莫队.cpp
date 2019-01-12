#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int N,M,res;
struct Node{
    int val;
    int id;
    bool operator < (const Node &p) const {return val<p.val;}
}a[maxn];
bool cmpid(const Node &x,const Node &y) {return x.id<y.id;}

int b[maxn];
int pos[maxn],cnt[maxn],block;                  //块数
int ans[maxn];
int v[maxn];            //离散化
struct Query{
    int L,R,id;
}Q[maxn];
bool cmp1(const Query& x,const Query& y){       //根据所属块的大小排序
    if(pos[x.L]==pos[y.L]) return x.R<y.R;
    return pos[x.L]<pos[y.L];
}  

void add(int pos)
{
    int id = v[a[pos].id];
    if(cnt[id]==b[pos]-1) res++;
    else if(cnt[id]==b[pos]) res--;
    cnt[id]++;    
}

void pop(int pos)
{
    int id = v[a[pos].id];
    if(cnt[id]==b[pos]) res--;
    else if(cnt[id]==b[pos]+1) res++;
    cnt[id]--;
}

//#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    int cas=1;
    while(scanf("%d%d",&N,&M)==2){
        block = ceil(sqrt(1.0*N));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i].val);
            a[i].id = i;
            b[i] = a[i].val;
            pos[i]=i/block;
        }
        //离散化
        sort(a+1,a+N+1);
        int tag = 1;
        v[a[1].id] = tag;
        for(int i=2;i<=N;++i){
            if(a[i].val == a[i-1].val) v[a[i].id] = tag;
            else v[a[i].id] = ++tag; 
        }
        sort(a+1,a+N+1,cmpid);

        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
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
        for(int i=1;i<=M;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}