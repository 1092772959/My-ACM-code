#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include<map>
#define LL long long
using namespace std;
const int MOD=1e9+7;
int diec[20][10];
map<LL,int> M;
long long ans=0;
int x;
long long pow(long long x,int n)
{
    long long y=1;
    long long u=x%MOD;
    while(n){
        if(n&1) y=y*u%MOD;
        n>>=1;
        u=u*u%MOD;
    }
    return y;
}
void dfs(int s,int e,int flag,long long res)
{
    if(e==s){
        if(flag)
            ++M[res];
        else
            ans+=M[x*pow(res,MOD-2)%MOD];
    }
    else{
        for(int i=0;i<6;i++)
            dfs(s+1,e,flag,res*diec[s][i]%MOD);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ans=0;
        M.clear();
        int n;
        scanf("%d%d",&n,&x);
        for(int i=0;i<n;i++){
            for(int j=0;j<6;j++){
                scanf("%d",&diec[i][j]);
            }
        }
        dfs(0,n/2,1,1);
        dfs(n/2,n,0,1);
        cout<<ans<<endl;
    }
}
