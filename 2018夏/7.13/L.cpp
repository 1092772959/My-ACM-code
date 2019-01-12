#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =2e4+5;
const LL INF = (LL)(1<<60);
LL a[maxn];
int main()
{
    int N;
    while(scanf("%d",&N)==1){
        for(int i=0;i<N;++i){
            scanf("%lld",&a[i]);
        }
        sort(a,a+N);
        bool flag = false;
        for(int i=N-1;i>=2;--i){
            if(a[i]<a[i-1]+a[i-2]){
                flag= true;
                //cout<<a[i]<<" "<<a[i-1]<<" "<<a[i-2]<<endl;
                break;
            }
        }
        if(!flag) printf("impossible\n");
        else printf("possible\n");
    }
    return 0;
}
