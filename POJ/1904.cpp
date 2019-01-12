#include<iostream>
#include<stdio.h>
#include<cstring>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn =4e3+5,maxm = 3e5+5;
const int INF =0x3f3f3f3f;
struct Edge{int to,next;}edges[maxm];
int head[maxn],tot;
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
int sccnum[maxn];
void init(int N)
{
    tot=dfn=scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v){
    edges[tot] = (Edge){v,head[u]};
    head[u] = tot++;
}

void Tarjan(int u)
{
    int v;
    pre[u]=low[u]=++dfn;
    S.push(u);
    for(int i=head[u];~i;i=edges[i].next){
        v= edges[i].to;
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
            if(x==u)break;
        }
    }    
}
int Scan()     //输入外挂
{
    int res=0,ch,flag=0;
    if((ch=getchar())=='-')
        flag=1;
    else if(ch>='0'&&ch<='9')
        res=ch-'0';
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-'0';
    return flag?-res:res;
}
void Out(int a)    //输出外挂
{
    if(a>9)
        Out(a/10);
    putchar(a%10+'0');
}

int res[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,u,v,k,tmp;
    while(scanf("%d",&N)==1){
        init(N*2);
        for(int i=1;i<=N;++i){
            k = Scan();
            while(k--){
                v = Scan();
                AddEdge(i,v+N);
            }
        }
        for(int i=1;i<=N;++i){
            u = Scan();
            AddEdge(u+N,i);
        }
        for(int i=1;i<=2*N;++i){
            if(!pre[i])
                Tarjan(i);
        }
        for(int u=1;u<=N;++u){
            int cnt=0;
            for(int i=head[u];~i;i=edges[i].next){
                int v = edges[i].to;
                if(sccno[u]==sccno[v]){
                    res[cnt++] = v-N;
                }
            }
            sort(res,res+cnt);
            Out(cnt);
            for(int i=0;i<cnt;++i){
                putchar(' ');
                Out(res[i]);
            }
            putchar('\n');
        }
    }
    return 0;
}
