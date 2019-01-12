#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
LL c1[maxn],c2[maxn];

void mhs(int n)
{
    for(int i=0;i<=n;i++){
        c1[i]=1;
        c2[i]=0;
    }
    for(int i=2;i*i<=n;i++){
        for(int j=0;j<=n;j++)
        for(int k=0;k+j<=n;k+=i*i){
            c2[j+k]+=c1[j];
        }
        for(int j=0;j<=n;j++){
                c1[j]=c2[j];
                c2[j]=0;
            }
        }
    }

    int main(){
        int T,M,num,t,x,cas=1;
        int N,k,mod;
        #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
        #endif
        while(scanf("%d",&N),N){
            mhs(N);
            printf("%lld\n",c1[N]);
        }
        return 0;
    }