#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn = 1e3+5,maxm = 5e5+5;
int N,M;
struct Node{
    int K[maxn];
}link[maxn];
int cnt[maxn];
struct Edge{
    int to,next;
}edges[maxm];
int head[maxn],tot;
bool used[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edges[tot].to = v;
    edges[tot].next = head[u];
    head[u] = tot++;
}

bool dfs(int u,int limit){
    int v;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v]){
            used[v]=true;
            if(cnt[v]<limit){
                link[v].K[cnt[v]++]=u;
                return true;
            }
            for(int j=0;j<cnt[v];++j){
                if(dfs(link[v].K[j],limit)){
                    link[v].K[j]=u;
                    return true;
                }
            }
        }
    }
    return false;
}

bool hungary(int limit){
    memset(cnt,0,sizeof(cnt));
    for(int u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(!dfs(u,limit)) return false;     //只要有一个人不能匹配则失败
    }
    return true; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,u,v,tmp,k;
    char c;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        init();
        for(int u=1;u<=N;++u){
            char op[maxn];
            scanf("%s",op);
            while(true){
                scanf("%d%c",&v,&c);
                AddEdge(u,v+1);
                if(c == '\n') break;
            }            
        }
        int L=1,R=N,mid,ans=N;
        while(L<=R){
            mid = (L+R)>>1;
            if(hungary(mid)){
                ans = mid;
                R = mid-1;
            }
            else L=mid+1; 
        }
        printf("%d\n",ans);
    }
    return 0;
}

