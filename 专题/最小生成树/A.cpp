#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
const int maxn=30;
const int maxm=100+10;
 
struct Edge{
    int u,v,dist;
    bool operator<(const Edge &rhs)const{return dist<rhs.dist;}
};

struct Kruskal{
    int n,m;
    Edge edges[maxm];
    int fa[maxn];
    int findset(int x){ return fa[x]==-1?x:fa[x]=findset(fa[x]); }
 
    void init(int n){
        this->n=n;
        m=0;
        memset(fa,-1,sizeof(fa));
    }
 
    void AddEdge(int u,int v,int dist){
        edges[m++]=Edge{u,v,dist};
    }
    
    int kruskal(){
        int sum=0,cnt=0;
        sort(edges,edges+m);
        for(int i=0;i<m;i++){
            int u=edges[i].u, v=edges[i].v;
            if(findset(u) != findset(v)){
                sum +=edges[i].dist;
                fa[findset(u)] = findset(v);
                if(++cnt>=n-1)  return sum;
            }
        }
        return -1;
    }
}G;

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,u,v,tmp,k;
    char c[5];
    while(scanf("%d",&N)==1){
        if(!N) break;
        G.init(N);
        for(int i=1;i<N;++i){
            scanf("%s %d",c,&k);
            u = c[0]-'A'+1;
            for(int j=1;j<=k;++j){
                scanf("%s%d",c,&tmp);
                v = c[0]-'A'+1;
                G.AddEdge(u,v,tmp);
            }
        }
        int res = G.kruskal();
        printf("%d\n",res);
    }

    return 0;
}