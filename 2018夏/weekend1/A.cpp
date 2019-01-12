#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
const int INF = 0x3f3f3f3f;
typedef long long ll;

int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        int mn1=INF,mn2=INF,mx=-INF,e;
        for(int i =0;i<n;++i){
            scanf("%d",&e);
            if(e<mn1)    mn1 = e;
            if(e>mx)    mx =e ;
        }
        for(int i=0;i<m;++i){
            scanf("%d",&e);
            if(e<mn2)    mn2 =e;
        }
        if(2*mn1>=mn2 || mx >= mn2)  printf("-1\n");
        else{
            printf("%d\n",max(2*mn1,mx));
        }
    }
    return 0;
}