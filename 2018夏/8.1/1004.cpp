#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e2+5;
const int mod = 1e9+7;
struct Item{
    int a,b,sum;
    double rate;
    bool operator < (const Item &p) const{return rate>p.rate;}
}p[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    int a,b;
    scanf("%d",&T);
    while(T--){
        int res=0;
        int cnt=0;
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i){
            scanf("%d%d",&p[i].a,&p[i].b);
            p[i].sum = p[i].a +p[i].b;
            p[i].rate = 1.0*p[i].a/(p[i].a+p[i].b);
       }
       sort(p+1,p+N+1);
       for(int i=1;i<=N;++i){ 
           if(M/p[i].sum>=1)
               res++;
            else break;
            tmp = M/p[i].sum;                               //筛
            int next = p[i].a*tmp + max(M%tmp-p[i].b,0);
            M=next;
       }
       printf("%d\n",res);
    }
    return 0;
}