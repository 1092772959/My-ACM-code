#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1000015;

LL n,m;
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

int getfactors(){
    int ans=1;
    LL tmp = n;
    if(n/m <m) return 0;
    for(int i= 1;prime[i]<=tmp/prime[i];++i){
        int c = 0;
        while( tmp %prime[i]==0){
            c++;
            tmp/=prime[i];
        }
        ans *=(c+1);
    }
    if(tmp>1) ans<<=1;              //如果n还没分解完，说明还有一对约数对
    ans>>=1;                        //因为每对约数对都被枚举了两次，所以除2
    for(int i=1;i<m;++i)            //小于m的约数对要减去
        if(n%i==0) 
            ans--;
    return ans;
}