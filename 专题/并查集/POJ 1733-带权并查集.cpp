#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const int INF= 0x3f3f3f3f;
int fa[maxn];
int dist[maxn];
void init(int N)
{
    for(int i=0;i<=N;++i) fa[i]=i,dist[i]=0;
}

int Find(int x)
{
    if(fa[x]==x) return x;
    int f = fa[x];
    fa[x] = Find(fa[x]);
    dist[x] =(dist[x]+dist[f])%2;
    return fa[x];
}

bool Union(int a,int b,int op)
{
    int roota= Find(a),rootb = Find(b);
    if(roota==rootb && (dist[a]+op)%2!=dist[b]) return false;
    fa[rootb] = roota;
    dist[rootb] =(op+dist[a]-dist[b]+2)%2; 
    return true;
}

map<int,int> dp;

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    int a,b;
    char op[6];
    while(scanf("%d%d",&N,&M)==2){
        dp.clear();
        init(10000);
        int cnt=1,ans=0;
        for(int i=1;i<=M;++i){
            scanf("%d%d%s",&a,&b,op);
            if(!dp[a-1]) dp[a-1]= cnt++;
            if(!dp[b]) dp[b] = cnt++;
            if(op[0]=='e'){
                if(!Union(dp[a-1],dp[b],0) && !ans) ans=i;
            }
            else{
                if(!Union(dp[a-1],dp[b],1) && !ans) ans=i;
            }
        }
        if(!ans) ans=M+1;
        printf("%d\n",ans-1);
    }
    return 0;
}
