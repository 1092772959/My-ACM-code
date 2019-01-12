#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef int LL;
const int maxn =1e4+5;
struct Point
{
    LL x,y;
    int id;
}p[maxn];
bool cmp(Point a,Point b){
    if(a.x==b.x)    return a.y<b.y;
    return a.x<b.x;
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=3*n;i++){
            scanf("%lld%lld",&p[i].x,&p[i].y);
            p[i].id=i;
        }
        sort(p+1,p+3*n+1,cmp);
        for(int i=1;i<=3*n;i+=3){
            printf("%d %d %d\n",p[i].id,p[i+1].id,p[i+2].id);
        }
    }
    return 0;
}
