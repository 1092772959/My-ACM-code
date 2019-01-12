#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
vector<int> p[maxn];
bool is[maxn];

void pre()
{
    for(int i=2;i<maxn;i+=2) {
        p[i].clear();
        p[i].push_back(2);
    }
    for(int i=3;i<maxn;i+=2){
        if(is[i]) continue;
        for(int j=i;j<maxn;j+=i){
            is[j] = true;
            p[j].push_back(i);
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    pre();
    int T,cas=1; scanf("%d",&T);
    while(T--){
        int a,b,c,d,k;
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        if(k==0){
            printf("Case %d: 0\n",cas++);
            continue;
        }
        b/=k,d/=k;
        if(b>d) swap(b,d);
        LL ans=0;
        for(int i=1;i<=d;++i){
            int tot = min(i,b);
            ans += tot;
            int up = 1<<p[i].size(),len = p[i].size();
            for(int j=1;j<up;++j){
                int cnt=0,ji=1;

                for(int k=0;k<len;++k){
                    if(j&(1<<k)){
                        cnt++;
                        ji *=p[i][k];
                    }
                }

                if(cnt&1) ans -= tot/ji;
                else ans +=tot/ji; 
            }
        }
        printf("Case %d: %lld\n",cas++,ans);
    }
    return 0;
}