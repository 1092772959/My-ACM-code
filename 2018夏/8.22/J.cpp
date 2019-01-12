#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
LL MW[1<<5],SW[1<<5];
LL ans = 0;
LL x[10];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
	int T,N,M,K;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d %d",&N, &M, &K);
        memset(MW,-INF,sizeof(MW));
        memset(SW,-INF,sizeof(SW));
        int up = 1<<K;
        for(int i=1;i<=N;++i){
            LL val; scanf("%lld",&val);
            for(int j = 0;j<K;++j) scanf("%lld",&x[j]);
            for(int s=0;s<up;++s){
                LL tmp = val;
                for(int j=0;j<K;++j){
                    if(s&(1<<j)) tmp += x[j];
                    else tmp -= x[j];
                }
                MW[s] = max(MW[s],tmp);
            }
        }  
        for(int i=1;i<=M;++i){
            LL val; scanf("%lld",&val);
            for(int j = 0;j<K;++j) scanf("%lld",&x[j]);
            for(int s=0;s<up;++s){
                LL tmp = val;
                for(int j=0;j<K;++j){
                    if(s&(1<<j)) tmp += x[j];
                    else tmp -= x[j];
                }
                SW[s] = max(SW[s],tmp);
            }
        }
        LL ans = 0;
        for(int s=0;s<up;++s){
            ans = max(ans,MW[s]+SW[up-1-s]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
