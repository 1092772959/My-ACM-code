
#include<iostream>
#include<cstring>
#include<cstdio>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 10007
#define inf 0x3f3f3f3f
#define maxm 2007
int pos[maxm],tree[maxm];

void add(int p,int val,int id){
    while(p < maxm){
        if(val < tree[p]){
            tree[p] = val;
            pos[p] = id;
        }
        p += p&(-p);
    }
}
int query(int p){
    int id=-1,val=inf;
    while(p > 0){
        if(tree[p] < val){
            val = tree[p];
            id = pos[p];
        }
        p -= p&(-p);
    }
    return id;
}
 
struct Node{
    int x,y,id,xsy;
};
int comp(Node a,Node b){
    if(a.x == b.x) return a.y > b.y;
    return a.x > b.x;
}
int compxsy(Node a,Node b){
    return a.xsy < b.xsy;
}
struct Edge{
    int u,v,w;
    Edge(int _u=0,int _v=0,int _w=0){
        u =_u,v=_v,w=_w;
    }
};
vector<Edge> edge;
Node point[maxn];
Node P[maxn];
int dist(Node a,Node b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}
void ManhaTon(int n){
    for(int i = 0;i < n; i++)
        point[i].xsy = point[i].x-point[i].y;
    sort(point,point+n,compxsy);
    int cnt = 1,f=-inf;
    for(int i = 0;i < n; i++){
        if(point[i].xsy != f){
            cnt++;
            f = point[i].xsy;
        }
        point[i].xsy = cnt;
    }
    sort(point,point+n,comp);
 
    for(int i = 0;i < maxm; i++)
        tree[i] = inf,pos[i]=-1;
    for(int i = 0;i < n; i++){
        int u = point[i].id;
        int v = query(point[i].xsy);
        if(v != -1)
            edge.push_back(Edge(u,v,dist(P[u],P[v])));
        add(point[i].xsy,point[i].x+point[i].y,u);
    }
}
 
 
void buildEdge(int n){
    edge.clear();
    for(int j = 0;j < 4; j++){
        for(int i = 0;i < n; i++)
            point[i] = P[i];
        for(int i = 0;i < n; i++){
            if(j == 1) swap(point[i].x,point[i].y);
            else if(j == 2)
                point[i].y = -point[i].y;
            else if(j==3){
                swap(point[i].x,point[i].y);
                point[i].y = -point[i].y;
            }
        }
        ManhaTon(n);
    }
}
int pre[maxn];
int find(int u){
    if(u == pre[u]) return u;
    return pre[u] = find(pre[u]);
}
int compEdge(Edge a,Edge b){
    return a.w < b.w;
}
int MST(int n,int k){
    for(int i = 0;i < n; i++)
        pre[i] = i;
    sort(edge.begin(),edge.end(),compEdge);
    int d = 0;
    for(int i = 0;i < edge.size() ;i++){
        if(n == k) return d;
        d = edge[i].w;
        int f1 = find(edge[i].u);
        int f2 = find(edge[i].v);
        if(f1 == f2) continue;
        pre[f1] = f2;
        n--;
    }
    return d;
}
 
int main(){
    int n,k;
    while(scanf("%d%d",&n,&k)!=EOF){
        for(int i = 0;i < n; i++){
            scanf("%d%d",&P[i].x,&P[i].y);
            P[i].id = i;
        }
        buildEdge(n);
        printf("%d\n",MST(n,k));
    }
    return 0;
}
 
