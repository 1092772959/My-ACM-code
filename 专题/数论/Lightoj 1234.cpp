#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e8+5;
const int INF =0x3f3f3f3f;
double ans[maxn/50+1];
void pre()
{
    ans[0] = 0, ans[1] = 1.0;
    double t = 1.0;
    for(int i =2;i<maxn;++i){
        t+= 1.0/i;
        if(i%50==0){
            ans[i/50] =t;
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T,N,u,v,tmp,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        int st = N/50,len = N%50;
        double res= ans[st];
        int base = st*50;
        for(int i=1;i<=len;++i)
            res+= 1.0/(i+base);
        printf("Case %d: %.10f\n",cas++,res);
    }
    return 0;
}
