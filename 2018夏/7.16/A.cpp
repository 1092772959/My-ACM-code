#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e3+5;
const int mod = 7901;
#define PI 3.1415926
#define eps 1e-10
//#define LOCAL

double area(double r)
{
    return PI*r*r;
}

int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int T,N;
    scanf("%d",&T);
    while(T--){
        double R,r;
        scanf("%lf%lf",&R,&r);
        if(area(R)-2*area(r)>eps) puts("1");
        else puts("2");
    }    
    return 0;
}