#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN = 1e6+5;   //待筛的区间[L,R]长度
const int N = 50001;//保证大于(2^31-1)的算数平方根
bool prime[MAXN];
bool seive[N];
typedef long long LL;
LL L,R,len;
 
void seg_seive(LL L,LL R)   //区间筛法
{
    len=R-L+1;
    for(int i=0;i<len;i++) prime[i]=1;
    if(1-L>=0) prime[1-L]=0;   //易错因为1不是素数也不是合数，这也是区间筛的一个易错bug
    for(LL i=2; i*i<=R ;i++){
        if(seive[i]){
            for(LL j=max((LL)2,(L-1+i)/i)*i;j<=R;j+=i)  //第二个易错点，j必须从大于1，因为L可能小于i，但是seive[i]是素数。
                prime[j-L]=false;
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int T,cas=1;
    for(int i=2;i<N;i++) seive[i]=1;
    for(int i=2;i*i<N;i++)  //预处理
        if(seive[i])
            for(int j=2*i;j<N;j+=i)
                seive[j]=false;
        
    while(scanf("%lld%lld",&L,&R)==2){
        seg_seive(L,R);
        int lmax,rmax,lmin,rmin;
        int mmax=-1,mmin=(1<<30);
        int t=-1;
 
        for(int i=0;i<len;i++)
            if(prime[i]){
                if(t>=0){
                    if(mmax<i-t) mmax=i-t,lmax=t+L,rmax=i+L;
                    if(mmin>i-t) mmin=i-t,lmin=t+L,rmin=i+L;
                    t=i;
                }
                else t=i;
            }
        if(mmax>0) printf("%d,%d are closest, %d,%d are most distant.\n",lmin,rmin,lmax,rmax);
        else puts("There are no adjacent primes.");
    }
    return 0;
}