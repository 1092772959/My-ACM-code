#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;   //待筛的区间[L,R]长度
const int N = 50001;//保证大于(2^31-1)的算数平方根
bool prime[MAXN];
bool seive[N];
typedef long long LL;
int L,R,len;
 
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
    int T,cas=1; scanf("%d",&T);
    for(int i=2;i<N;i++) seive[i]=1;
    for(int i=2;i*i<N;i++)  //预处理
        if(seive[i])
            for(int j=2*i;j<N;j+=i)
                seive[j]=false;
        
    while(T--){
        scanf("%d%d",&L,&R);
        seg_seive(L,R);
        int mmax=-1,mmin=(1<<30);
        int t=-1;
        int res=0;
        for(int i=0;i<len;i++)
            if(prime[i]){
                res++;
            }
        printf("Case %d: %d\n",cas++,res);
    }
    return 0;
}