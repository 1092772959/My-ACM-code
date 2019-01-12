#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100000+5;
bool vis[maxn];
int prime[maxn],mu[maxn];
void init_mu(int n=maxn){
    int cnt=0;
    mu[1]=1;
    for(int i=2;i<n;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<cnt&&i*prime[j]<n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) {mu[i*prime[j]]=0;break;}
            else { mu[i*prime[j]]=-mu[i];}
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    init_mu();
    int T,cas=1; scanf("%d",&T);
    while(T--){
        LL a,b,c,d,k;
        scanf("%lld %lld %lld %lld %lld ",&a,&b,&c,&d,&k);
        if(k==0){
            printf("Case %d: 0\n",cas++);
            continue;
        }
        b/=k,d/=k;
        if(b>d) swap(b,d);
        LL res=0, tmp = 0;
        for(LL i=1;i<=b;++i){
            res += (LL)mu[i] * (b/i)*(d/i);
            tmp += (LL)mu[i] * (b/i)*(b/i);
        }
        printf("Case %d: %lld\n",cas++,res-tmp/2);
    }
    return 0;
}

