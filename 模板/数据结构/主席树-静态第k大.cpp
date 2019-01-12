#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int N = 200005;
const int INF = 0x3f3f3f3f;
int n,q,tot;
struct lp{
    int l,r,sum;
    lp(){l=r=sum=0;}
}cw[N*20];
int ar[N],br[N],now[N];
int root[N];
void update(int l,int r,int last,int &cur,int x){
    cw[++tot]=cw[last];
    cw[tot].sum++;
    cur=tot;
    if(l==r)return;
    int mid = (l+r)>>1;
    if(x<=mid){
        update(l,mid,cw[last].l,cw[cur].l,x);
    }else {
        update(mid+1,r,cw[last].r,cw[cur].r,x);
    }
}
int query(int l,int r,int last,int cur,int k){
    if(l==r)return l;
    int l1=cw[last].l,l2=cw[cur].l,r1=cw[last].r,r2=cw[cur].r;
    int summ=cw[l2].sum-cw[l1].sum;
    int mid=(l+r)>>1;
    if(k<=summ){
        return query(l,mid,cw[last].l,cw[cur].l,k);
    }else{
        return query(mid+1,r,cw[last].r,cw[cur].r,k-summ);
    }
}
int main(){
    while(~scanf("%d%d",&n,&q)){
        memset(root,0,sizeof(root));
        cw[0].l=cw[0].r=cw[0].sum=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&br[i]);
            ar[i]=br[i];
        }
        sort(br+1,br+1+n);
        int k=1;
        for(int i=2;i<=n;++i){
            if(br[i]!=br[i-1])br[++k]=br[i];
        }
        tot=0;
        for(int i=1;i<=n;++i){
            now[i]=lower_bound(br+1,br+1+k,ar[i])-br;
        }
        for(int i=1;i<=n;++i){
            update(1,k,root[i-1],root[i],now[i]);
        }
        while(q--){
            int u,v;
            scanf("%d%d",&u,&v);
            int L=1,R=v-u+1,mid,ans=1;
            while(L<=R){//二分的写法大同小异，用自己习惯的写法
                mid=(L+R)>>1;
                int tmp=query(1,k,root[u-1],root[v],v-u+1-mid+1);
                if(mid>br[tmp]){
                    ans=mid-1;
                    R=mid-1;
                }else{
                    ans=mid;
                    L=mid+1;
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
