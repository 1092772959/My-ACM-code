
#include<iostream>
#include<stdio.h>
#include<set>
#include<cstring>
using namespace std;
const int maxn =205;
int dp[maxn][maxn];

int sg(int w,int h)
{
    if(dp[w][h]!=-1) return dp[w][h];
    set<int> s;
    for(int i =2;w-i>=2;++i) s.insert(sg(i,h)^sg(w-i,h));
    for(int i=2;h-i>=2;++i) s.insert(sg(w,i)^sg(w,h-i));

    int res=0;
    while(s.count(res)) res++;
    return dp[w][h]=res;
}

void solve(int w,int h)
{
    if(sg(w,h)) printf("WIN\n");
    else printf("LOSE\n");
}

int main()
{
    memset(dp,-1,sizeof(dp));
    dp[2][2]=0;
    int w,h;
    while(~scanf("%d%d",&w,&h)){
        solve(w,h);
    }
    return 0;
}