#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =605;
const int INF=0x3f3f3f3f;
bool is[maxn],vis[maxn];
int val[maxn];
bool is_prime(int n)
{
    if(n==1) return false;
    for(int i=2;i*i<=n;++i){
        if(n%i==0) return false;
    }
    return true;
}
int N;
int d[maxn],G[maxn][maxn];

int prim(){
    int MST =0;
    memset(vis,0,sizeof(vis));
    vis[1] = true;
    for(int i=1;i<=N;++i) d[i] =G[1][i];
    for(int i=1;i<N;++i){
        int min = INF;
        int u;
        for(int j=1;j<=N;++j){
            if(!vis[j] && min>d[j]){
                u =j;
                min = d[j];    
            }
        }
        if(min==INF) return -1;            
        MST+=min;
        vis[u] = true;
        for(int j =1;j<=N;++j){
            if(!vis[j] && d[j]>G[u][j]){
                d[j] = G[u][j];
            }
        }
    }
    return MST;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int M,u,v,tmp,T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i=1;i<=N;++i){
            scanf("%d",&val[i]);
            is[i]= is_prime(val[i]);
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(i==j) {G[i][j]=INF;continue;}
                if(is[i] || is[j] || is_prime(val[i]+val[j])){
                    tmp = min(val[i],min(val[j],abs(val[i]-val[j])));
                    G[i][j]= tmp;
                }
                else G[i][j] =INF;
            }
        }
        printf("%d\n",prim());
    }    
    return 0;
}