#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
int cnt(int N)
{
    int cnt=0;
    while(N){
        cnt+=N/5;
        N/=5;
    }
    return cnt;
}

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int T,N,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        int L=1,R=1000000000,ans=-1;
        while(L<=R){
            int m = L+(R-L)/2;
            int re = cnt(m);
            if(re==N){
                while(m%5!=0) m--;
                ans = m;
                break;
            }
            else if(re<N)  L = m+1;
            else R = m-1;
        }
        printf("Case %d: ",cas++);
        if(ans>0) printf("%d\n",ans);
        else printf("impossible\n");
    }   
    return 0;
}