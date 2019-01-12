#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
vector<int> p[maxn];
int L[maxn],C[maxn],N;
int dp[305][(1<<9)];

int gcd(int a,int b){
    if(b==0)
        return a;
    return gcd(b,a%b);
}

int f(int j,int k)      //取L[j]质因子组成状态为k的数
{
    int res=1,pos=0;
    while(k){
        if(k&1)     res*=p[j][pos];
        k>>=1;
        pos++;
    }
    return res;
}

int t(int x,int num)            //返回代表二进制状态的数
{
    int len = p[x].size(),res=0;
    for(int i=len-1;i>=0;--i){     //逆序
        res<<=1;
        if(num%p[x][i]==0)  res++;
    }
    return res;             //如果num不能被L[i]的任意一种质因子组合正处，则num与L[i]互质，状态即全零
}

void facto(int x)       //质因子分解
{
    int tmp = L[x];
    for(int i=2;i*i<=L[x];++i){
        if(tmp%i==0){
            p[x].push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp>1)  p[x].push_back(tmp);
}

int main()
{
    while(~scanf("%d",&N)){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=N;++i){
            scanf("%d",&L[i]);
            p[i].clear();
            facto(i);               //质因子分解
        }
        for(int i=1;i<=N;++i)    scanf("%d",&C[i]);
        for(int i=0;i<=N;++i){
            for(int j=0;j<=(1<<9);++j){
                dp[i][j]=INF;                   //init
            }
        }
        int L1,L2,tmp,gd,zone;
        for(int i=1;i<=N;++i){
            L1 = p[i].size();
            dp[i][(1<<L1)-1]=min(dp[i][(1<<L1)-1],C[i]);
            for(int j=1;j<i;++j){
                L2= p[j].size();
                for(int k=0;k<(1<<L2);++k){     //枚举L[j]的每种质因子组合状态
                    if(dp[j][k]==INF)   continue;
                    tmp = f(j,k);               //获取该状态的值
                    tmp = gcd(tmp,L[i]);        
                    zone = t(i,tmp);    
                    dp[i][zone] = min(dp[i][zone],dp[j][k]+C[i]);
                }
            }
        }
        int res=INF;
        for(int i=1;i<=N;++i)   res=min(dp[i][0],res);
        if(res==INF)    printf("-1\n");
        else printf("%d\n",res);
    }
    return 0;
}
