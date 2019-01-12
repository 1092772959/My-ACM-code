#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
typedef long long LL;
LL cnt[maxn];

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    LL N,M,s,t,u,v,tmp;
    LL X;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&X,&N);
        memset(cnt,0,sizeof(cnt));
        if(N==1) {
            printf("%lld\n",X);
            continue;
        }
        LL cir = N-1;
        LL tmp = X/(N-1);
        X -= cir*tmp;
        cnt[1]+=(tmp+1)/2;
        for(int i=2;i<=N-1;++i){
            cnt[i]+=tmp;
        }
        cnt[N]+=tmp/2;
        if(tmp&1){
            for(int i=N;X;i--,X--)
                cnt[i]++;
        }
        else{
            for(int i=1;X;i++,X--)
                cnt[i]++;
        }
        for(int i=1;i<N;++i)
            printf("%lld ",cnt[i]);
        printf("%lld\n",cnt[N]);
    }
    return 0;
}

