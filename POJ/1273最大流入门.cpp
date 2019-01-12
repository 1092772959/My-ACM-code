#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN=1010;//点数的最大值
const int MAXM=4010;//边数的最大值
#define captype int

struct SAP_MaxFlow{
    struct EDGE{
        int to,next;
        captype cap;
    }edg[MAXM];
    int eid,head[MAXN];
    int gap[MAXN];  
    int dis[MAXN];  
    int cur[MAXN];  
    int pre[MAXN];
    
    void init(){
        eid=0;
        memset(head,-1,sizeof(head));
    }
    void AddEdge(int u,int v,captype c,captype rc=0){
        edg[eid].to=v; edg[eid].next=head[u];
        edg[eid].cap=c;  head[u]=eid++;
        edg[eid].to=u; edg[eid].next=head[v];
        edg[eid].cap=rc; head[v]=eid++;
    }
    int maxFlow_sap(int sNode,int eNode, int n){//n是包括源点和汇点的总点个数，这个一定要注意
        memset(gap,0,sizeof(gap));
        memset(dis,0,sizeof(dis));
        memcpy(cur,head,sizeof(head));
        pre[sNode] = -1;
        gap[0]=n;
        captype ans=0;  
        int u=sNode;
        while(dis[sNode]<n){   
            if(u==eNode){  
                captype Min=INF ;
                int inser;
                for(int i=pre[u]; i!=-1; i=pre[edg[i^1].to])    
                if(Min>edg[i].cap){
                    Min=edg[i].cap;
                    inser=i;
                }
                for(int i=pre[u]; i!=-1; i=pre[edg[i^1].to]){
                    edg[i].cap-=Min;
                    edg[i^1].cap+=Min;  
                }
                ans+=Min;
                u=edg[inser^1].to;
                continue;
            }
            bool flag = false; 
            int v;
            for(int i=cur[u]; i!=-1; i=edg[i].next){
                v=edg[i].to;
                if(edg[i].cap>0 && dis[u]==dis[v]+1){
                    flag=true;
                    cur[u]=pre[v]=i;
                    break;
                }
            }
            if(flag){
                u=v;
                continue;
            }
            int Mind= n;
            for(int i=head[u]; i!=-1; i=edg[i].next)
            if(edg[i].cap>0 && Mind>dis[edg[i].to]){
                Mind=dis[edg[i].to];
                cur[u]=i;
            }
            gap[dis[u]]--;
            if(gap[dis[u]]==0) return ans;  
            dis[u]=Mind+1;
            gap[dis[u]]++;
            if(u!=sNode) u=edg[pre[u]^1].to;  //退一条边
        }
        return ans;
    }
}F;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
	int N,M;
    int u,v,tmp;
    while(scanf("%d %d",&N,&M)==2){
        F.init();
        for(int i=1;i<=N;++i){
            scanf("%d %d %d",&u,&v,&tmp);
            F.AddEdge(u,v,tmp);
        }
        int res = F.maxFlow_sap(1,M,M);
        printf("%d\n",res);
    }
    return 0;
}
