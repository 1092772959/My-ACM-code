#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn =305;
const int INF= 1000000;

int w[maxn][maxn];
int m,n;//n左m右 
int cx[maxn],cy[maxn];//顶标 
bool usex[maxn],usey[maxn];//本回合使用的x，y 
int link[maxn];//link[i]=x代表：在y图中的i与x相连 

int A,B;

bool dfs(int u){
    usex[u]=1;
    for(int i=1;i<=B;i++)
        if(!usey[i]&&cx[u]+cy[i]==w[u][i]){
            usey[i]=1;
            if(link[i]==-1||dfs(link[i])){ 
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
    for(int i=1;i<=A;i++)
        for(int j=1;j<=B;j++)
            cx[i]=max(cx[i],w[i][j]);
    for(int i=1;i<=A;i++){      
        while(1){
            int d=INF;
            memset(usex,0,sizeof(usex));
            memset(usey,0,sizeof(usey));
            if(dfs(i))break;
            for(int i=1;i<=A;i++)
                if(usex[i])
                    for(int j=1;j<=B;j++)
                        if(!usey[j])d=min(d,cx[i]+cy[j]-w[i][j]);
            if(d==INF)return -1;
            for(int i=1;i<=A;i++)
                if(usex[i])cx[i]-=d;
            for(int i=1;i<=B;i++)
                if(usey[i])cy[i]+=d;
        }
    }

    int ans=0;
    for(int i=1;i<=B;i++){
        if(~link[i]){
            ans -= w[link[i]][i];
        }
    }
    return ans;
}

int nd[maxn][maxn];
int sp[maxn][maxn];
int ct[maxn][maxn][maxn];
int cas;

int cnt1[maxn],cnt2[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int T,tmp;
    int u,v,k;
    while(scanf("%d%d%d",&n,&m,&k)==3){
        if(!n && !m && !k) break;
        
        for(int i=1;i<=n;++i){
            for(int j=1;j<=k;++j){
                scanf("%d",&nd[i][j]);
            }
        }
        
        for(int i=1;i<=m;++i){
            for(int j=1;j<=k;++j){
                scanf("%d",&sp[i][j]);
            }
        }
        
        for(int i=1;i<=k;++i){
            for(int j=1;j<=n;++j){
                for(int t = 1;t<=m;++t){
                    scanf("%d",&ct[i][j][t]);
                }
            }
        }
        bool flag = true;
        for(int cas=1;cas<=k;++cas){
            int need = 0,supply =0;
            for(int i=1;i<=n;++i)   need+= nd[i][cas];
            for(int i=1;i<=m;++i)   supply +=sp[i][cas];
            if(need>supply){
                flag = false;
                break;
            }
        }

        if(!flag){
            puts("-1");
            continue;
        }

        int tot = 0;
        for(int cas = 1;cas<=k;++cas){
            A=B=0;
            for(int i=1;i<=n;++i){
                for(int j=1;j<=nd[i][cas];++j){
                    cnt1[++A] = i;      
                }
            }
            for(int i=1;i<=m;++i){
                for(int j=1;j<=sp[i][cas];++j){
                    cnt2[++B] = i;
                }
            }
            for(int i=1;i<=A;++i){
                for(int j=1;j<=B;++j){
                    w[i][j] = -ct[cas][cnt1[i]][cnt2[j]];
                }
            }
            int tmp = KM();
            tot+=tmp;
        }
        printf("%d\n",tot);
    }
    return 0;
}
