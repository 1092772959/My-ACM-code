#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
using namespace std;
typedef long long LL;
const int maxn = 2e4+5;
const int INF= 0x3f3f3f3f;
struct Edge{
    int u,v;
}E[maxn];
struct Query{
    int op,a,b;
    LL ans;
}p[maxn*3];
LL w[maxn];
LL dist[maxn];
int fa[maxn];
int maxid[maxn];
inline int Find(int x) {return fa[x]==x ?x: fa[x]=Find(fa[x]);}
//void init(int N){ for(int i=0;i<N;++i) fa[i]=i,dist[i]=w[i],maxid[i]=i;}
void Union(int a,int b){
    a = Find(a),b = Find(b);
    if(a!=b){
        fa[a] = b;
        if(dist[b]<dist[a] || dist[b]==dist[a] && maxid[b]>maxid[a]){
            dist[b]=dist[a];
            maxid[b]=  maxid[a];
        }
    }
}

map<int,map<int,int> > tag;

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K,cas=1;
    char op[10];
    int mk = 0;
    while(scanf("%d",&N)==1){
        if(mk) printf("\n");
        mk = 1;
        for(int i=0;i<N;++i) {
            scanf("%lld",&w[i]);
            fa[i]=maxid[i]=i;
            dist[i]=w[i];
        }
        tag.clear();
        scanf("%d",&M);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            E[i].u =u , E[i].v=v;
        }
        scanf("%d",&Q);
        for(int i=1;i<=Q;++i){
            scanf("%s%d",op,&p[i].a);
            if(op[0]=='d') {
                p[i].op=0;
                scanf("%d",&p[i].b);
                tag[p[i].a][p[i].b]=tag[p[i].b][p[i].a]=1;                  //被删边的标记
            }
            else p[i].op = 1;                       //0删边，1查询
        }
        //因为并不是把边全删完，建立最终状态
        for(int i=1;i<=M;++i){
             if(tag[E[i].u][E[i].v]) continue;      //这条边不在
             else Union(E[i].u,E[i].v);
        }

        for(int i=Q;i>=1;--i){
            if(!p[i].op) Union(p[i].a,p[i].b); 
            else{
                u = Find(p[i].a);
                if(dist[u]>w[p[i].a]) p[i].ans=maxid[u];
                else p[i].ans= -1;
            }    
        }
        for(int i=1;i<=Q;++i){
            if(p[i].op) printf("%lld\n",p[i].ans);
        }
    }
    return 0;
}