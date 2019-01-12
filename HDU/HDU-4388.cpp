#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T,n,e;
    scanf("%d",&T);
    for(int k=1;k<=T;++k){
        scanf("%d",&n);
        int cnt =n;
        for(int i=0;i<n;++i){
            scanf("%d",&e);
            while(e){
                if(e&1) cnt++;
                e>>=1;
            }
        }
        printf("Case %d: ",k);
        if(cnt&1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}