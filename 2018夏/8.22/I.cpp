#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e7+5;
int phi[maxn*2];              //欧拉函数
bool check[maxn*2];
int prime[maxn*2];
LL res[maxn];
void Euler()
{             //欧拉函数表
    memset(check,0,sizeof(check));
    phi[1] = 1;
    int tot=0;
    int up = maxn*2;
    for(int i=2;i<up;++i){
        if(!check[i]){
            prime[tot++] = i;
            phi[i] = i-1;
        }
        for(int j=0;j<tot;++j){
            if(i*prime[j]>up) break;
            check[i*prime[j]]  =true;
            if(i % prime[j] ==0){
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            else{
                phi[i*prime[j]] = phi[i] * (prime[j]-1);
            }
        }
    }
    for(int i=2;i<maxn;++i){
        res[i] = res[i-1]+phi[i<<1]/2;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    
    Euler();
    
    int T; scanf("%d",&T);
    while(T--){
        int i; scanf("%d",&i);
        printf("%lld\n",res[i]);
    }
    return 0;
}

