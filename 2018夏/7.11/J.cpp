#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;

int n1,n2;
int main()
{
    while(scanf("%d%d",&n1,&n2)==2){
        int d1,d2;
        if(n1>n2)  {
            d1=(360-n1)+n2;
            d2=-(n1-n2);
        }
        else{ 
            d1=n2-n1;
            d2=-(360-n2)-n1;
        }
        int res;
        if(d1<=abs(d2)) res=d1;
        else res=d2;
        printf("%d\n",res);
    }    
    return 0;
}