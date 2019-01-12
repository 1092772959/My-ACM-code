#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;
const int maxn =205;
const int INF=0x3f3f3f3f;
int w[maxn][maxn];
int m,n;//n左m右 
int cx[maxn],cy[maxn];//顶标 
bool usex[maxn],usey[maxn];//本回合使用的x，y 
int link[maxn];//link[i]=x代表：在y图中的i与x相连 

void init()
{
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            w[i][j]=-INF;           //初始为负
}

bool dfs(int u){
    usex[u]=1;
    for(int i=1;i<=m;i++)
        if(!usey[i]&&cx[u]+cy[i]==w[u][i]){
            usey[i]=1;
            if(link[i]==-1||dfs(link[i])){
                link[i]=u;
                return true;   
            }
        }
    return false;
}
int KM(){
    memset(cy,0,sizeof(cy));
    memset(cx,-1,sizeof(cx));
    memset(link,-1,sizeof(link));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cx[i]=max(cx[i],w[i][j]);
    for(int i=1;i<=n;i++){      
        while(1){
            int d=INF;
            memset(usex,0,sizeof(usex));
            memset(usey,0,sizeof(usey));
            if(dfs(i))break;
            for(int i=1;i<=n;i++)
                if(usex[i])
                    for(int j=1;j<=m;j++)
                        if(!usey[j])d=min(d,cx[i]+cy[j]-w[i][j]);
            if(d==INF)return -1;
            for(int i=1;i<=n;i++)
                if(usex[i])cx[i]-=d;
            for(int i=1;i<=m;i++)
                if(usey[i])cy[i]+=d;
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++)   
        if(~link[i]) ans+=w[link[i]][i];
    return ans;
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M); n=m=N;
        init();
        for(int i=1;i<=M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            w[u][v]=max(w[u][v],-tmp);
        }
        int res=-KM();
        printf("%d\n",res);
    }
    return 0;
}