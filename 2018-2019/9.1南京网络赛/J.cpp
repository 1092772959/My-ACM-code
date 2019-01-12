#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e7+5;
bool vis[maxn];
int prime[maxn];
LL f[maxn];
LL res[maxn];
void init_f(int n){
    int cnt=0;
    f[1]=1;
    for(int i=2;i<n;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            f[i]=2;
        }
        for(int j=0;j<cnt&&i*prime[j]<n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                if(i%(prime[j]*prime[j])==0) f[i*prime[j]]=  0;
                else f[i*prime[j]]= f[i]/2;
                break;
            }
            else{ 
                f[i*prime[j]]= f[i]*2;
            }
        }
    }
    for(int i=1;i<maxn;++i) res[i] = res[i-1]+f[i];
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    init_f(maxn);
    int T; scanf("%d",&T);
    while(T--){
        int n; scanf("%d",&n);
        printf("%lld\n",res[n]);
    }
    return 0;
}