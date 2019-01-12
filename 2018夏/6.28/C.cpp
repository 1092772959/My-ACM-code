#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
map<LL,LL> mp;
int main()
{
    LL u,v,w,res;
    int q,op;
    while(scanf("%d",&q)==1){
        for(int i=0;i<q;++i){
            scanf("%d",&op);
            
            if(op==1){
                scanf("%lld%lld%lld",&u,&v,&w);
                while(u!=v){
                    if(u>v) swap(u,v);
                    mp[v]+=w;
                    v>>=1;
                }
            }
            else{
                scanf("%lld%lld",&u,&v);
                res=0;
                while(u!=v){
                    if(u>v) swap(u,v);
                    res+=mp[v];
                    v>>=1;
                }
                printf("%lld\n",res);
            }
        }
    }
    return 0;
}