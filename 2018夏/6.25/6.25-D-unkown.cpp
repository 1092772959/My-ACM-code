#define N 1000005
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
__int64 d[N],t[N],m,n;
struct node
{
    __int64 f;
    __int64 x;
    __int64 y;
};
node p[N];
int main()
{
    __int64 i,j,c,s,k;
    while(~scanf("%I64d",&m)){
        d[0]=0;
        s=1;
        for(i=1;i<=m;i++){
            scanf("%I64d",&p[i].f);
            if(p[i].f==1){
                scanf("%I64d",&p[i].x);
                d[i]=d[i-1]+1;
                if(s<=100000)
                    t[s++]=p[i].x;
            }
            else{
                scanf("%I64d%I64d",&p[i].x,&p[i].y);
                d[i]=d[i-1]+p[i].x*p[i].y;
                for(int h=1;h<=p[i].y&&s<=100000;h++){
                    for(j=1;j<=p[i].x&&s<=100000;j++)
                        t[s++]=t[j];
                }
            }
        }
        scanf("%I64d",&n);
        for(i=0;i<n;i++){
            scanf("%I64d",&c);
            k=(upper_bound(d+1,d+m+1,c)-d)-1;
            if(d[k]==c){
                if(p[k].f==1)
                    printf("%I64d\n",p[k].x);
                else
                    printf("%I64d\n",t[p[k].x]);
            }
            else{
                c-=d[k];
                c%=p[k+1].x;
                if(c==0)
                    c=p[k+1].x;
                printf("%I64d\n",t[c]);
            }
        }
    }
    return 0;
}