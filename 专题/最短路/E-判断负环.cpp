#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long LL;
const int maxn =1e2+5;

struct Edge{
    int from,to,next;
    double rate,com;  
}edges[maxn<<2];
int tot,head[maxn];
double d[maxn];

void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}

void Addedge(int u,int v,double rate,double com)
{
    edges[tot].from = u;
    edges[tot].to = v;
    edges[tot].rate  = rate;
    edges[tot].com = com;
    edges[tot].next = head[u];
    head[u]=tot++;
}

bool bellman_ford(int s,int N,double val)
{
    memset(d,0,sizeof(d));
    d[s] =val;
    for(int i=1;i<=N;++i){
        bool update = false;
        for(int j=0;j<tot;++j){
            Edge e = edges[j];
            if(d[e.to] < (d[e.from]-e.com) * e.rate){
                d[e.to] = (d[e.from]-e.com) * e.rate;
                update = true;
            }
        }
        if(!update) break;
        if(i==N) return true;
    }
    return false;
}

int main()
{
    int T,cas=1,S,N,M,u,v,tmp;
    double val,R1,C1,R2,C2;
    while(scanf("%d%d%d%lf",&N,&M,&S,&val)==4){
        init();
        for(int i=1;i<=M;++i){
            scanf("%d%d %lf%lf%lf%lf",&u,&v,&R1,&C1,&R2,&C2);
            Addedge(u,v,R1,C1);
            Addedge(v,u,R2,C2);
        }
        if(bellman_ford(S,N,val)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
