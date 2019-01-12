#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stack>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#define MAXN 1000100
#define LL long long
using namespace std;
const int maxn = 1e6+5;

bool notprime[maxn];
int prime[maxn+1];              //prime[0] 表示当前范围内有多少素数,prime[i] 表示第i个素数是多少

void pre()
{
    memset(notprime,0,sizeof(notprime));
    notprime[0] = notprime[1] = true;
    memset(prime,0,sizeof(prime));
    for(int i=2;i<maxn;++i){
        if(!notprime[i]) prime[++prime[0]] = i;
        for(int j=1 ; j<=prime[0] && prime[j] <= maxn / i ;++j){
            notprime[prime[j]*i] = true;
            if(i%prime[j]==0) break;
        }
    }
}

int gcd(int a,int b){	return b?gcd(b,a%b):a;}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
	pre();
	LL n;
	int t,i;
	int cas=0;
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		int bz=0;
		if(n<0)	n=-n,bz=1;
		int ans=0;
		for(i=1; i<=prime[0]&&prime[i]*prime[i]<=n;i++){
			if(n%prime[i]==0){
				int cnt=0;
				while(n%prime[i]==0){
					cnt++;
					n/=prime[i];
				}
				if(ans==0) ans=cnt;
				else ans=gcd(ans,cnt);
			}
			if(n==1) break;
		}
		if(n>1) ans=1;
		if(bz)
			while(ans%2==0)	ans/=2;
		printf("Case %d: %d\n",++cas,ans);
	}
	return 0;
}
