#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int INF =0x3f3f3f3f;
typedef long long LL;
int a[10];
int dp[10][82][82][82];

int dfs(int pos,int sum,int remain,int mod,bool limit){
    if(pos==-1) return (sum==mod && !remain);
    if(dp[pos][sum][remain][mod]!=-1 && !limit) return dp[pos][sum][remain][mod];
    int up = limit? a[pos]:9;
    int res=0;
    for(int i=0;i<=up;++i){
        if(i+sum>mod) break;
        res+=dfs(pos-1,sum+i,(remain*10+i)%mod,mod,limit && i==a[pos]);
    }
    if(!limit) dp[pos][sum][remain][mod] = res;
    return res;
}

int solve(int N)
{
    int pos=0,res=0;
    int x=N;
    while(x){
        a[pos++]=x%10;
        x/=10;
    }
    int len = min(pos*9,81);
    for(int i=1;i<= len;++i)
        res+=dfs(pos-1,0,0,i,true);
    
    return res;
}

int main(){
    int T,M,num,t,x;
    int N;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int L,R,cas=1;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&L,&R);
        printf("Case %d: %d\n",cas++,solve(R)-solve(L-1));
    }
    return 0;
}