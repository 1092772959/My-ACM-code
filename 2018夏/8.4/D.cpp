#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
typedef long long LL;
#define size 3
const int maxn = 1e4+5;
const int INF= 0x3f3f3f3F;
const LL mod = 200907;
int one[3][3] = {1,0,0,0,1,0,0,0,1};
int base[3][3] = {1,2,1,1,0,0,0,0,1};
int zero[3][3] = {0,0,0,0,0,0,0,0,0};
struct Mat{
    LL M[size][size];   
    Mat(int tmp[][size]){
        for(int i=0;i<size;++i){
            for(int j=0;j<size;++j){
                M[i][j] = tmp[i][j];
            }
        }
    }
};

Mat mul(Mat &a,Mat &b)
{
    Mat c(zero);
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            for(int k=0;k<size;++k){
                c.M[i][j] = (c.M[i][j]+a.M[i][k]*b.M[k][j]%mod)%mod;
            }
        }
    }
    return c;
}

Mat mpow(Mat a,int n)
{
    Mat res(one);
    while(n){
        if(n&1) res = mul(res,a);
        a = mul(a,a);
        n>>=1;
    }
    return res;
}


LL solve(int n)
{
    if(n==1) return 1;
    else if(n==2) return 2;
    Mat a(base);
    Mat res = mpow(a,n);
    return res.M[1][0]*2%mod;
}

LL a[5000];

void pre()
{
    a[0]=0,a[1]=1,a[2]=2;
    for(int i=3;i<3200;++i){
        a[i]=(2*a[i-2]%mod+a[i-1]+1)%mod;
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    pre();
    while(scanf("%d",&N)==1){
        if(!N) break;
        N%=3186;
        printf("%lld\n",a[N]);
    }
    return 0;
}