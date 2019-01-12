#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
vector<LL> fac;

const int maxn = 2650000;

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
    for(int i=1;i<prime[0];++i){
        fac.push_back((LL)prime[i]*prime[i]*prime[i]);
    }
}


LL temp;
void dfs(int index,LL mult,int cnt,int all,LL M)
{
    if(mult>M) return;
    if(cnt==all){
        temp += M/mult;
        return;
    }
    for(int i=index;fac[i]<=M;++i){
        if(mult>M/fac[i]) break;
        dfs(index+1,mult*fac[i],cnt+1,all,M);
    }
}

LL solve(LL M)
{
    LL res=0;
    int num = fac.size();
    for(int i=1;;++i){
        temp =0 ;
        dfs(0,1,0,i,M);
        if(temp){
            if(i&1) res+= temp;
            else res-=temp;
        }
        else break;
    }
    return M-res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    pre();
    while(T--){
        LL L,R; scanf("%lld %lld",&L,&R);
        printf("%lld\n",solve(R-1)-solve(L-1));
    }
    return 0;
}