#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e3+5;
int res[maxn];

int main()
{
    int T,N,X;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&X,&N);
        int tmp = X/N,m=X%N;
        if(!tmp){
            printf("-1\n");
            continue;
        }
        int p1 = N-m;
        for(int i=1;i<=p1;++i){
            printf("%d ",tmp);
        }
        for(int i=p1+1;i<=N;++i){
            printf("%d ",tmp+1);
        }
        printf("\n");
        
    
    }
    return 0;
}