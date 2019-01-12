/*
莫队

*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int a[maxn],b[maxn];
int pos[maxn];
int block;                  //块数
ll cnt[maxn],ans;
ll res[maxn];
struct Query
{
    int L,R,id;
    ll ans;                 //存数据
}Q[maxn];

bool cmp1(const Query& x,const Query& y){       //根据所属块的大小排序
    if(pos[x.L] ==pos[y.L] )  return x.R<y.R;
    return x.L<y.L;
}  
bool cmp_id(const Query &p1,const Query &p2)    {return p1.id<p2.id;}

void update(int pos,int step)
{
    ans -=cnt[a[pos]]*cnt[a[pos]]*cnt[a[pos]];
    cnt[a[pos]] = cnt[a[pos]] +step;
    ans +=cnt[a[pos]]*cnt[a[pos]]*cnt[a[pos]];
}

int main()
{
    int N,q;
    while(cin>>N){
        memset(cnt,0,sizeof(cnt));
        memset(b,0,sizeof(b));
        memset(a,0,sizeof(a));
        //block = (int)(sqrt(1.0*N)+0.5);          //块
        block = ceil(sqrt(1.0*N));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
            b[i]=a[i];
            pos[i]=i/block;
        }
        sort(b+1,b+N+1);                        //离散化

        map<ll,int> m;
        for(int i=1;i<=N;++i)
            m[b[i]]=i;
        for(int i=1;i<=N;++i)   
            a[i]=m[a[i]];

        scanf("%d",&q);
        for(int i=0;i<q;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id=i;
            Q[i].ans=0;
        }

        sort(Q,Q+q,cmp1);               //查询排序
        int curL=2,curR=1;
        ans=0;
        for(int i =0;i<q;++i){
            while(curL>Q[i].L)  update(--curL,1);
            while(curR<Q[i].R)  update(++curR,1);
            while(curL<Q[i].L)  update(curL++,-1);
            while(curR>Q[i].R)  update(curR--,-1);
            res[Q[i].id]=ans;
        }
        for(int i=0;i<q;++i)
            printf("%I64d\n",res[i]);
    }
    return 0;
}

