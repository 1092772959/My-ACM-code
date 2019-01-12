#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =4e4+5;
LL c1[maxn],c2[maxn];
LL dp[maxn];
void mhs()
{
    for(int i=0;i<maxn;i++){
        c1[i]=1;
        c2[i]=0;
    }
    for(int i=2;i<=3;i++){
        for(int j=0;j<maxn;j++)
        for(int k=0;k+j<maxn;k+=i){
            c2[j+k]+=c1[j];
        }
        for(int j=0;j<maxn;j++){
                c1[j]=c2[j];
                c2[j]=0;
        }
    }
}

void pre()
{
    dp[0]=1;
    for(int i=1;i<=3;++i){
        for(int j=i;j<maxn;++j){
            dp[j]+=dp[j-i];
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
        mhs();
        while(scanf("%d",&N)==1){
            
            printf("%lld\n",c1[N]);
        }
        return 0;
    }