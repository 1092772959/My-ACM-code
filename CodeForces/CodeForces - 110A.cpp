#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    LL N;
    while(~scanf("%lld",&N)){
        bool flag = true;
        int cnt=0;
        while(N){
            int re = N%10;
            if(re==4 ||re==7) cnt++;
            N/=10;
        }
        if(!cnt) {
            printf("NO\n");continue;
        }
        while(cnt && flag){
            int re = cnt%10;
            if(re!=4 &&re!=7) flag = false;
            cnt/=10;
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
