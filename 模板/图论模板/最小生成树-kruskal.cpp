#include<bits/stdc++.h>
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
                if(++cnt>=n-1) return sum;
            }
        }
        return -1;
    }
}G;