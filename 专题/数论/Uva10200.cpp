#include<bits/stdc++.h>
using namespace std;
#define maxn 10005
typedef long long LL;
int sum[maxn];
bool isprime(int x)
{
    if(x == 1) return false;
    int m = (int)sqrt(x + 0.5);
    for(int i = 2; i <= m; i++){
        if(x % i == 0) return false;
    }
    return true;
}

void init()
{
    sum[0] = 1;
    for(int i = 1; i <= 10000; i++){
        sum[i] = sum[i - 1];
        if(isprime(i * i + i + 41)) sum[i]++;
    } 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    init();
    int L,R;
    while(scanf("%d%d",&L,&R)==2){
        int cnt = L==0? sum[R]:sum[R] - sum[L-1];
        double res = 1.0*cnt/(R-L+1);
        printf("%.2f\n",res*100+1e-5);
    }
    return 0;
}
