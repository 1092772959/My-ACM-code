#include<iostream>
#include<cstring>
#include<stdio.h>
#include<map>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
#define LOCAL
using namespace std;
typedef double LL;
const int maxn =1e3+5;
const double INF = 1e100;

const double wv=10.0 * 1000.0 / 60.0,sv=40.0 * 1000.0 / 60.0;

struct Edge{
    int to,next;
    LL val;
    bool walk;
};
struct HeapNode{
    LL d;           //费用或路径
    int u;
    bool operator < (const HeapNode & rhs) const{return d > rhs.d;}  
};
struct Dijstra{
    int n,m,tot;
    Edge edges[maxn<<8];
    bool used[maxn];
    LL d[maxn];
    int head[maxn];

    void init(int n){
        this->n = n;
        this->tot=0;
        memset(head,-1,sizeof(head));
    }

    void Addedge(int u,int v ,LL dist,bool walk){
        edges[tot].to = v;
        edges[tot].val = dist;
        edges[tot].next = head[u];
        edges[tot].walk = walk;
        head[u] = tot++;
    }

    void dijkstra(int s){   
        memset(used,0,sizeof(used));
        priority_queue<HeapNode> Q;
        for(int i=0;i<=n;++i)    d[i]=INF;
        d[s]=0.0;
        Q.push((HeapNode){d[s],s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;
            if(used[u])    continue;
            used[u]= true;
            for(int i=head[u];~i;i=edges[i].next){
                Edge & e = edges[i];
                double cost;
                if(e.walk) cost = e.val/wv;
                else cost = e.val/sv;
                if(d[e.to] > d[u] + cost){
                    d[e.to] = d[u] +cost;
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
}G;

struct Point{
    double x,y;
}p[maxn];

double dist(Point &a,Point &b){
    double d1 = (double)(a.x-b.x);
    double d2 = (double)(a.y-b.y);
    return sqrt(d1*d1+d2*d2);
}

int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    G.init(100);
    int N=2,M,u,v,x,y,nx,ny;
    Point a,b; b.x=-1,b.y=-1;
    scanf("%lf%lf%lf%lf",&p[1].x,&p[1].y,&p[2].x,&p[2].y);
    while(scanf("%lf%lf",&a.x,&a.y)==2){
        if(a.x>=0){
            p[++N]=a;
            if(b.x>=0){
                double d = dist(p[N-1],p[N]);
                G.Addedge(N-1,N,d,false);
                G.Addedge(N,N-1,d,false);
            }
        }
        b=a;
    }
    for(int i=1;i<=N;++i){
        for(int j=i+1;j<=N;++j){
            double d=dist(p[i],p[j]);
            G.Addedge(i,j,d,true);
            G.Addedge(j,i,d,true);
        }
    }
    G.n = N;
    G.dijkstra(1);
    printf("%.0f\n",G.d[2]);
    return 0;
}