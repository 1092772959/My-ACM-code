#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =605;
const int INF=0x3f3f3f3f;

int gcd(int a,int b)
{
    if(!b) return a;
    else return gcd(b,a%b);
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,u,v,tmp,T;
    while(scanf("%d%d",&N,&M)==2){
        if(N==-1) break;
        else if(gcd(N,M)==1) printf("YES\n");
        else printf("POOR Haha\n");
    }
    return 0;
}