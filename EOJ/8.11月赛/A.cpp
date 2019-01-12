#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e2+5;
int G[maxn][maxn];
int to[maxn][maxn];
int res[maxn][maxn];

int main() 
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int n,m,h,w;
    while(scanf("%d%d",&n,&m)==2){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                scanf("%d",&G[i][j]);
            }
        }
        scanf("%d%d",&h,&w);
        for(int i=1;i<=h;++i){
            for(int j=1;j<=w;++j){
                scanf("%d",&to[i][j]);
            }
        }
        
        bool front = true;
        for(int i=1;i<=n-h+1;++i){
            for(int j=1;j<=m-w+1;++j){
                res[i][j] = 0;
                for(int k=1;k<=h;++k){
                    for(int t=1;t<=w;++t){
                        res[i][j] +=G[i+k-1][j+t-1]*to[k][t];
                    }
                }
            }
        }
        

        for(int i=1;i<=n-h+1;++i){
            for(int j=1;j<=m-w+1;++j){
                printf("%d%c",res[i][j],j==m-w+1?'\n':' ');
            }
        }
    }
    return 0;
}