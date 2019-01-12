#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
const int INF = 0x3f3f3f3f;
struct Edge{
    int v,id,next;  
}edges[maxn<<2];
int head[maxn],tot;
int d[maxn];
set<int> sta[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));    
}

void AddEdge(int u,int v,int id)
{
    edges[tot] = (Edge){v,id,head[u]};
    head[u] = tot++;
}

struct Node{
    int val,u;
    int pre,fa;
    bool operator <(const Node &p) const{return val>p.val;}
};
void BFS(int s,int t)
{
    memset(d,INF,sizeof(d));
    d[s] = 0;
    priority_queue<Node> Q;
    Q.push((Node){d[s],s,-1,-1});
    while(!Q.empty()){
        Node x=  Q.top();Q.pop();
        int pre = x.pre, u = x.u;
        if(x.val> d[u]) continue;
        else if(x.val==d[u]){
            bool tag = true;
            if(sta[u].find(pre)!=sta[u].end()) 
                continue;
            sta[u].insert(pre);
        }
        else{
            d[u] = x.val;
            sta[u].clear();
            sta[u].insert(pre);
        }

        for(int i=head[u];~i;i=edges[i].next){
            int v = edges[i].v,now = edges[i].id;
            if(v==x.fa) continue;                       //反向边
            if((d[u]+(pre!=now))<=d[v]){
                d[v] = d[u] + (pre!=now);
                if(v!=t) Q.push((Node){d[v],v,now,x.u});
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M;
    int u,v,id;
    while(scanf("%d%d",&N,&M)==2){
        for(int i=1;i<=N;++i) sta[i].clear();
        init();
        while(M--){
            scanf("%d%d%d",&u,&v,&id);
            AddEdge(u,v,id);
            AddEdge(v,u,id);
        }
        BFS(1,N);
        if(d[N]==INF) d[N]=-1;
        printf("%d\n",d[N]);
    }
    return 0;
}