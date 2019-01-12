#include<bits/stdc++.h>
using namespace std;

int s,t,x;


int main()
{
    while(scanf("%d%d%d",&t,&s,&x)==3){
        if(x<t){
            printf("NO\n");
            continue;
        }
        if((x-t)%s==0){
            printf("YES\n");
        }
        else if(x-t>s && (x-t-1)%s==0){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}