#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5+5;
int n,h[maxn];
int L[maxn],R[maxn],st[maxn];

void solve()
{
    ll res=0;
    int t=0;        //栈大小
    for(int i=0;i<n;++i){
        while(t>0 && h[st[t-1]]>=h[i]) t--;
        L[i]=t==0? 0:(st[t-1]+1);
        st[t++]=i;
    }
    for(int i=n-1;i>=0;--i){
        while(t>0 && h[st[t-1]]>=h[i]) t--;
        R[i] = t ==0 ? n:st[t-1];
        st[t++]=i;
    }
    for(int i=0;i<n;++i){
        res=max(res,(ll)(h[i]*(R[i]-L[i])));
    }
    printf("%lld\n",res);
}


int main()
{
    while(~scanf("%d",&n),n){
        for(int i=0;i<n;++i)
            scanf("%d",&h[i]);
        solve();
    }
    return 0;
}