#include<bits/stdc++.h>
using namespace std;
const int maxn =1030;
const int mod = 1e9+7;
typedef long long LL;
void add(int &a,int b){a=a+b<mod?a+b:a+b-mod;}
void del(int &a,int b){a=a-b<0?a-b+mod:a-b;}
int dp[maxn],ans[10],cnt[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v;
    char op[5];
    scanf("%d",&T); 
    while(T--){
        scanf("%d%d",&N,&M);
        int tot=1<<N;
        for(int i=0;i<tot;++i){
            dp[i]=0;
            cnt[i] = __builtin_popcount(i);
        }
        dp[0]=1;
        while(M--){
            scanf("%s%d%d",op,&u,&v);
            memset(ans,0,sizeof(ans));
            u--,v--;
            int S = (1<<u)|(1<<v);
            if(op[0]=='+'){
                for(int t=tot-1;~t;--t)
                    if(!(t&S)) add(dp[t^S],dp[t]);
            }
            else{
                for(int t=0;t<tot;++t)
                    if(!(t&S)) del(dp[t^S],dp[t]);
            }
            for(int i=1;i<tot;++i) add(ans[cnt[i]],dp[i]);
            for(int i=2;i<=N;i+=2) printf("%d%c",ans[i],i<N?' ':'\n');
        }
    }
    return 0;
}
