#include<bits/stdc++.h>
using namespace std;
typedef int captype;
const int MAXN = 10005;
const int INF = 0x3f3f3f3f;

struct ISAP{
int n;//实际建图总点数（最好比图中总点数大一点）
struct Edge{
    int v,next;
    captype cap,flow;
}edge[MAXN*100];
    int cur[MAXN],head[MAXN],gap[MAXN],path[MAXN],dep[MAXN];
    int cnt=0;//实际存储总边数
    void init(int n){
        this -> n  =n;
        cnt=0;
        memset(head,-1,sizeof(head));
    }
    void AddEdge(int u,int v,captype w,captype rw=0)//加边 单向图三个参数  双向图四个
    {
        edge[cnt] = (Edge){v,head[u],w,0};
        head[u]=cnt++;
        edge[cnt] = (Edge){u,head[v],rw,0};
        head[v]=cnt++;
    }
    bool bfs(int s,int t){//其实这个bfs可以融合到下面的迭代里，但是好像是时间要长
        memset(dep,-1,sizeof(dep));
        memset(gap,0,sizeof(gap));
        gap[0]=1;
        dep[t]=0;
        queue<int>q;
        while(!q.empty())
        q.pop();
        q.push(t);//从汇点开始反向建层次图
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=edge[i].next){
                int v=edge[i].v;
                if(dep[v]==-1&&edge[i^1].cap>edge[i^1].flow)//注意是从汇点反向bfs，但应该判断正向弧的余量
                {
                    dep[v]=dep[u]+1;
                    gap[dep[v]]++;
                    q.push(v);
                    //if(v==s)//感觉这两句优化加了一般没错，但是有的题可能会错，所以还是注释出来，到时候视情况而定
                    //break;
                }
            }
        }
        return dep[s]!=-1;
    }
    captype isap(int s,int t){
        bfs(s,t);
        memcpy(cur,head,sizeof(head));
        int u=s;
        path[u]=-1;
        captype ans=0;
        while(dep[s]<n){//迭代寻找增广路
            if(u==t){
                captype f=INF;
                for(int i=path[u];i!=-1;i=path[edge[i^1].v])//修改找到的增广路
                    f=min(f,edge[i].cap-edge[i].flow);
                for(int i=path[u];i!=-1;i=path[edge[i^1].v]){
                    edge[i].flow+=f;
                    edge[i^1].flow-=f;
                }
                ans+=f;
                u=s;
                continue;
            }
            bool flag=false;
            int v;
            for(int i=cur[u];i!=-1;i=edge[i].next){
                v=edge[i].v;
                if(dep[v]+1==dep[u]&&edge[i].cap-edge[i].flow){
                    cur[u]=path[v]=i;//当前弧优化
                    flag=true;
                    break;
                }
            }
            if(flag){
                u=v;
                continue;
            }
            int x=n;
            if(!(--gap[dep[u]]))return ans;//gap优化
            for(int i=head[u];i!=-1;i=edge[i].next){
                if(edge[i].cap-edge[i].flow&&dep[edge[i].v]<x){
                    x=dep[edge[i].v];
                    cur[u]=i;//常数优化
                }
            }
            dep[u]=x+1;
            gap[dep[u]]++;
            if(u!=s)//当前点没有增广路则后退一个点
            u=edge[path[u]^1].v;
        }
        return ans;
    }
}F;
