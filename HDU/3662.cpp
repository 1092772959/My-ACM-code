#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

const int maxn =1e4+5;
struct Edge{
    int v,next;  
}edges[maxn];
int head[maxn],tot;
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
int sccnum[maxn];
void init()
{
    tot = dfn = scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(sccnum,0,sizeof(sccnum));
    memset(sccno,0,sizeof(sccno));
    memset(head,-1,sizeof(head));
}
void AddEdge(int u,int v)   {
    edges[tot] = (Edge){v,head[u]};
    head[u] = tot++;
}

void Tarjan(int u)
{
    int v;
    pre[u]=low[u]=++dfn;
    S.push(u);
    for(int i=head[u];~i;i=edges[i].next){
        v= edges[i].v;
        if(!pre[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!sccno[v]){
            low[u]=min(low[u],pre[v]);
        }
    }
    if(pre[u]==low[u]){
        int x;
        ++scc_cnt;
        for(;;){
            x = S.top();S.pop();
            sccno[x]=scc_cnt;
            sccnum[scc_cnt]++;
            if(x==u)break;
        }
    }    
}

const double eps = 0.0001;
struct node{
    int x,y;
}a[205];
double dis(const node &a,const node &b){
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
int n;
bool solve(double val){
    init();
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            if(dis(a[i],a[j])<2.0*val){
                //cout<<dis(a[i],a[j])<<endl;
                AddEdge(i,j+n);
                AddEdge(j,i+n);
            }
            if(dis(a[i],a[j+n])<2.0*val){
                //cout<<dis(a[i],a[j+n])<<endl;
                AddEdge(i,j);
                AddEdge(j+n,i+n);
            }            
            if(dis(a[i+n],a[j])<2.0*val){
                //cout<<dis(a[i+n],a[j])<<endl;
                AddEdge(i+n,j+n);
                AddEdge(j,i);
            }
            if(dis(a[i+n],a[j+n])<2.0*val){
                //cout<<dis(a[i+n],a[j+n])<<endl;
                AddEdge(i+n,j);
                AddEdge(j+n,i);
            }
        }
    }
    for(int i=0;i<2*n;i++)
        if(!pre[i]) Tarjan(i);
    for(int i=0;i<n;i++){
        if(sccno[i]==sccno[i+n]) return false;
    }
    return true;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int x,y;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            scanf("%d %d",&a[i].x,&a[i].y);
            scanf("%d %d",&a[i+n].x,&a[i+n].y);
        }
        double l=0.0,r=10000.0;
        while(r-l>eps){
            double m = l + (r-l)/2.0;
            //最大化最小值，就是找可行的最大值
            //cout<<m<<endl;
            if(solve(m)) l=m;
            else r=m;
        }
        printf("%.2f\n",l);

    }
    return 0;
}
/*
2
1 1 1 -1
-1 -1 -1 1
2
1 1 -1 -1
1 -1 -1 1

*/