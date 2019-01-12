#include<bits/stdc++.h>
using namespace std;
const int limit = 1e6;

int main()
{
    double n,p;
    while(scanf("%lf%lf",&n,&p)==2){
        double res=p/(n+1),tmp;
        double mm =(n+1);
        for(int x=2;x<=limit;++x){
            tmp = x*p;
            mm  *=(n+x);
            mm  /=(n-p+x);
            tmp /=mm;
            res = max(res,tmp);
        }
        printf("%.10f\n",res);
    }
    return 0;    
}

