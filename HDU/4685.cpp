#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<stack>
using namespace std;
typedef long long LL;
const int maxn =2e3+5;
int N;
struct Edge{
    int to,next;
}edges[maxn<<2],E[maxn<<2];
int head[maxn],tot,H[maxn],tt;
int linker[maxn];
bool used[maxn];
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
stack<int> S;
inline int min(int a,int b){
    return a>b? b:a;
}

void init()
{
    tt = tot = dfn = scc_cnt = 0;
    memset(H,-1,sizeof(H));
    memset(head,-1,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
}

void AddEdge(int u,int v)
{
    edges[tot] = (Edge){v,head[u]};
    head[u] = tot++;
}

void nAddEdge(int u,int v)
{
    E[tt] = (Edge){v,H[u]};
    H[u] = tt++;
}

bool dfs(int u){
    int v;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v]){
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v])){
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int u;
    int ans=0;
    memset(linker,-1,sizeof(linker));
    for(u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) ans++;
    }
    return ans; 
}

void Tarjan(int u)
{
    int v;
    pre[u]=low[u]=++dfn;
    S.push(u);
    for(int i=H[u];~i;i=E[i].next){
        v= E[i].to;
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
    int T; scanf("%d",&T);
    int M,u,v,tmp,cas=1;
    while(T--){
        init();
        N = Scan(); M = Scan();
        //scanf("%d%d",&N,&M);
        for(int u=1;u<=N;++u){
            int k; k=Scan();
            //scanf("%d",&k);
            while(k--){
                v = Scan();
                //scanf("%d",&v);
                AddEdge(u,v);           //二分图建图
            }
        }
        int cnt=hungary();
        
        int nx,ny; nx = ny = N+M-cnt;
        for(int i=1;i<=N;++i){
            for(int j=M+1;j<=ny;++j){
                AddEdge(i,j);
            }
        }        
        for(int i = N+1;i<=nx;++i){
            for(int j = 1;j<=ny;++j){
                AddEdge(i,j);
            }
        }

        hungary();
        
        for(int u=1;u<=nx;++u){
            for(int i=head[u];~i;i=edges[i].next){
                v = edges[i].to;
                nAddEdge(u,v+nx);                   //强连通建图
            }
        }
        
        for(int v=1;v<=ny;++v){
            nAddEdge(v+nx,linker[v]);              //反向
        }

        for(int i =1;i<=nx+ny;++i){
            if(!pre[i]){
                Tarjan(i);
            }
        }

        printf("Case #%d:\n",cas++);
        for(int u=1;u<=N;++u){
            int cnt=0;
            for(int i = H[u];~i;i=E[i].next){
                v = E[i].to;
                if(sccno[u]==sccno[v]){
                    res[cnt++] = v-nx;
                }
            }
            sort(res,res+cnt);
            //printf("%d",cnt);
            Out(cnt);
            for(int i=0;i<cnt;++i){
                putchar(' ');
                Out(res[i]);
                //printf(" %d",res[i]);
            }
            putchar('\n');
        }
    }
    return 0;
}

