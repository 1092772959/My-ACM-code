#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN=100010;//点数的最大值
const int MAXM=400010;//边数的最大值

struct Node{
    int from,to,next;
    int cap;
};

struct SAP_MaxFlow{
    int n,m;        //点数和边数
    int tol;
    int head[MAXN];
    int dep[MAXN];
    int gap[MAXN];//gap[x]=y :说明残留网络中dep[i]==x的个数为y
    Node edge[MAXM];

    void init(int N){
        n = N;
        tol=0;
        memset(head,-1,sizeof(head));
    }

    void AddEdge(int u,int v,int w)
    {
        edge[tol].from=u;
        edge[tol].to=v;
        edge[tol].cap=w;
        edge[tol].next=head[u];
        head[u]=tol++;
        edge[tol].from=v;
        edge[tol].to=u;
        edge[tol].cap=0;
        edge[tol].next=head[v];
        head[v]=tol++;
    }
    void BFS(int start,int end)
    {
        memset(dep,-1,sizeof(dep));
        memset(gap,0,sizeof(gap));
        gap[0]=1;
        int que[MAXN];
        int front,rear;
        front=rear=0;
        dep[end]=0;
        que[rear++]=end;
        while(front!=rear){
            int u=que[front++];
            if(front==MAXN)front=0;
            for(int i=head[u];i!=-1;i=edge[i].next){
                int v=edge[i].to;
                if(dep[v]!=-1)continue;
                que[rear++]=v;
                if(rear==MAXN)rear=0;
                dep[v]=dep[u]+1;
                ++gap[dep[v]];
            }
        }
    }
    int SAP(int start,int end){
        int res=0;
        BFS(start,end);
        int cur[MAXN];
        int S[MAXN];
        int top=0;
        memcpy(cur,head,sizeof(head));
        int u=start;
        int i;
        while(dep[start]<n){
            if(u==end){
                int temp=INF;
                int inser;
                for(i=0;i<top;i++)
                   if(temp>edge[S[i]].cap){
                       temp=edge[S[i]].cap;
                       inser=i;
                   }
                for(i=0;i<top;i++){
                    edge[S[i]].cap-=temp;
                    edge[S[i]^1].cap+=temp;
                }
                res+=temp;
                top=inser;
                u=edge[S[top]].from;
            }
            if(u!=end&&gap[dep[u]-1]==0)//出现断层，无增广路
              break;
            for(i=cur[u];i!=-1;i=edge[i].next)
               if(edge[i].cap!=0&&dep[u]==dep[edge[i].to]+1)
                 break;
            if(i!=-1){
                cur[u]=i;
                S[top++]=i;
                u=edge[i].to;
            }
            else{
                int min=n;
                for(i=head[u];i!=-1;i=edge[i].next){
                    if(edge[i].cap==0)continue;
                    if(min>dep[edge[i].to]){
                        min=dep[edge[i].to];
                        cur[u]=i;
                    }
                }
                --gap[dep[u]];
                dep[u]=min+1;
                ++gap[dep[u]];
                if(u!=start)u=edge[S[--top]].from;
            }
        }
        return res;
    }
}F;

int vis[1200];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int S,T,N,M,u,v,tmp,k;
    int op;
    while(scanf("%d%d",&N,&M)==2){
        F.init(N);
        k=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=N;++i){
            int x=0;
            for(int j=1;j<=M;++j){
                scanf("%d",&op);
                x<<=1;
                x+=op;                      //转换为二进制状态
            }
            vis[x]++;
        }
        for(int i=1;i<=1050;++i) if(vis[i]) k++;        //记录缩点后点数
        S=0;T=k+M+1; F.n=k+M+2;
        int id=0;
        for(int i=1;i<=1050;++i){
            if(!vis[i]) continue;
            id++;
            int sta = i,cnt = vis[i];
            for(int j=1,t=1;j<=sta;j<<=1,t++){
                if(j&sta) F.AddEdge(id,t+k,INF);
            }
            F.AddEdge(S,id,cnt);
        }
        for(int i=1;i<=M;++i){
            scanf("%d",&tmp);
            F.AddEdge(i+k,T,tmp);
        }
        if(F.SAP(S,T)==N) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

