#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn =20;
int G[maxn][maxn];
struct Node{
    int d,id;
    bool operator <(const Node &rhs)const{return d>rhs.d;} 
}p[maxn];

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(G,0,sizeof(G));
        for(int i=1;i<=N;++i){
            scanf("%d",&p[i].d);
            p[i].id = i;
        } 
        bool flag = true;
        while(true){
            sort(p+1,p+N+1);
            if(!p[1].d) break;
            int u = p[1].id;
            for(int j=2;p[1].d &&j<=N;++j){
                int v =p[j].id;
                if(!p[j].d) continue;
                G[u][v] = G[v][u] = 1;
                p[1].d--;
                p[j].d--;
            }
            if(p[1].d>0){
                flag = false;
                break;
            }
        }
        if(!flag) printf("NO\n");
        else{
            printf("YES\n");
            for(int i=1;i<=N;++i){
                for(int j=1;j<=N;++j){
                    printf("%d ",G[i][j]);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    return 0;
}
