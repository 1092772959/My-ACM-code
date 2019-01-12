#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =305;
const int INF=(1<<20)-1;

int w[maxn][maxn];
int m,n;//n左m右 
int cx[maxn],cy[maxn];//顶标 
bool usex[maxn],usey[maxn];//本回合使用的x，y 
int link[maxn];//link[i]=x代表：在y图中的i与x相连 
bool dfs(int u){
    usex[u]=1;
    for(int i=1;i<=m;i++)
        if(!usey[i]&&cx[u]+cy[i]==w[u][i]){
            usey[i]=1;
            if(link[i]==-1||dfs(link[i])){//注意这里要搜link[i]而不是i，因为我们只搜索x侧的，不需要搜索y侧的 
                link[i]=u;
                return 1;   
            }
        }
    return 0;
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
    for(int i=1;i<=m;i++){
        if(~link[i])ans+=w[link[i]][i];
    }
    return ans;
}

//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,s,t,u,v,T,tmp;
    while(scanf("%d",&N)==1){
        n=m=M=N;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                scanf("%d",&w[i][j]);
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}