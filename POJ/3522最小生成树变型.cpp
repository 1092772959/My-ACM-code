#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn=105;
const int maxm=1e4+5;
const int INF =0x3f3f3f3f;
struct Edge{
    int u,v,dist;
    bool operator<(const Edge &rhs)const{return dist<rhs.dist;}
};

struct Kruskal{
    int n,m;
    Edge edges[maxm];
    int fa[maxn];
    int findset(int x) { return fa[x]==x?x:fa[x]=findset(fa[x]); }
 
    void init(int n){
        this->n=n;
        m=0;
        memset(fa,-1,sizeof(fa));
    }
 
    void AddEdge(int u,int v,int dist){
        edges[m++]=Edge{u,v,dist};
    }
    
    int kruskal(){
        int ans,del=INF;
        sort(edges,edges+m);
        for(int i=0;i<=m-n+1;++i){      //枚举最小的m-n+2条边作为生成树的最小边
            for(int j=0;j<=n;++j) fa[j]=j;
            int sum=0,cnt=0;
            for(int j=i;j<m;j++){
                int u=findset(edges[j].u), v=findset(edges[j].v);
                if(u != v){
                    sum +=edges[j].dist;
                    fa[u] = v;
                    if(++cnt>=n-1){
                        if(edges[j].dist-edges[i].dist<del){
                            ans = sum;
                            del  = edges[j].dist - edges[i].dist;
                        }      
                        break;
                    }
                }
            }
        }
        if(del==INF) return -1;
        else return del;
    }
}G;

#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        G.init(N);
        for(int i=1;i<=M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            G.AddEdge(u,v,tmp);
        }
        printf("%d\n",G.kruskal());
    }
    return 0;
}
