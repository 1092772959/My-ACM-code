#include<bits/stdc++.h>
using namespace std;
const int maxn = 70010;
typedef long long LL;
typedef unsigned long long ULL;
int tot,v[70],a[70];

void pre()
{
    tot=0;
    memset(v,0,sizeof(v));
    for(int i=2;i<=64;++i){
        if(v[i]){
            a[tot++] = i;
            continue;
        }    
        for(int j=i*2;j<=64;j+=i) v[j]=1;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    set<ULL> res;
    res.insert(1);
    ULL up = (1LL)<<16;
    for(ULL i = 2;i<up;++i){
        int mx = ceil(64*log(2)/log(i))-1;
        ULL tmp = i * i * i * i;
        res.insert(tmp);
        for(int j=1;a[j]<=mx;++j){
            tmp *= (a[j]-a[j-1])==1? i:i*i;
            res.insert(tmp);
        }
    }
    for(auto &v :res){
        printf("%llu\n",v);
    }
    return 0;
}
