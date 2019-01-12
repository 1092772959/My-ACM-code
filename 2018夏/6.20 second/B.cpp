#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =50;
const int MOD = 1e9+7;
map<int,int> P;
int C[maxn][maxn];

void init()
{
    C[1][1]=C[1][0]=1;
    for(int i=2;i<maxn;++i){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }
}

void facto(int num)
{
    int tmp=num;
    for(int i=2;i*i<=num;++i){
        while(tmp%i==0){
            P[i]++;
            tmp/=i;
        }
    }
    if(tmp>1)   P[tmp]++;
}

inline int Comb(int n,int k)    {   return C[n][k];    }

int main()
{
    int N;
    init(); 
    while(~scanf("%d",&N)){
        P.clear();
        int tmp;
        for(int i=1;i<=N;++i){
            scanf("%d",&tmp);
            facto(tmp);
        }
        LL res=1,t;
        map<int,int>::iterator it;
        for(it = P.begin();it!=P.end();++it){
            res=(res*Comb(it->second+N-1,N-1))%MOD;
        }
        for(int i=1;i<=N-1;++i){
            t = 1;
            for(it = P.begin();it!=P.end();++it)
                t=(t*Comb(it->second+N-1-i,N-1-i))%MOD;
            t=(Comb(N,i)*t)%MOD;
            if(i&1) res=(res+MOD-t)%MOD;                    //容斥
            else res=(res+t)%MOD;
        }
        printf("%lld\n",res);
    }
    return 0;
}
