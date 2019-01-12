#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int pos[maxn];
struct Query{
    int L,R,id;
    bool operator <(const Query q) const{
        if(pos[L]==pos[q.L]) return R>q.R;
        return pos[L]<pos[q.L]; 
    }
}Q[maxn];
int a[maxn];
int ans[maxn];
int block;
int cnt[maxn];
int vis[maxn];
int res;
 
//区间是相反的
void add(int pos)
{
    cnt[a[pos]]++;
    if(cnt[a[pos]]==1) res++;
}
 
void pop(int pos){
    cnt[a[pos]]--;
    if(cnt[a[pos]]==0) res--;
}
 
int main()
{
    int n,q;
    while(scanf("%d%d",&n,&q)==2){
        memset(cnt,0,sizeof(cnt));       
        block  =ceil(sqrt(1.0*n));
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);   
            pos[i] = i/block;
        }
        for(int i=1;i<=q;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+q+1);
        int curL=0,curR=n+1;
        res=0;
        for(int i=1;i<=q;++i){
            //外区间缩
            while(curL>Q[i].L) pop(curL--);
            while(curR<Q[i].R) pop(curR++);
            //外区间扩
            while(curL<Q[i].L) add(++curL);
            while(curR>Q[i].R) add(--curR);
             
            ans[Q[i].id] = res;       
        }
        for(int i=1;i<=q;++i){
            printf("%d\n",ans[i]);
        }
    }
}