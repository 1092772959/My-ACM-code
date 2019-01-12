#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1000015;

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


int main(){
    int T,M,num,t,x,cas=1;
    int N;
    pre();
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d",&N)==1){
        if(N<=0) break;
        printf("%d: ",cas++);
        if(notprime[N]||N==2) printf("no\n");
        else printf("yes\n");
    }
    return 0;
}