#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f;
const int VM=1010;
const int EM=10010;
struct Edge{
    int to,nxt;
    int cap;
}edge[EM<<1];

int vis[VM][2],dis[VM][2];  
int head[VM],count[VM][2];  
int n,m,cnt;

void addedge(int cu,int cv,int cw){
    edge[cnt].to=cv;
    edge[cnt].cap=cw;
    edge[cnt].nxt=head[cu];
    head[cu]=cnt++;
}

void Dijkstra(int src,int des){
    memset(vis,0,sizeof(vis));
    memset(count,0,sizeof(count));
    int i=0;
    for(i=1;i<=n;i++){
        dis[i][0]=INF;
        dis[i][1]=INF;
    }
    dis[src][0]=0;
    count[src][0]=1;
    int j,k,tmp,flag;
    for(i=1;i<=2*n-1;i++){
        tmp=INF;    
        for(j=1;j<=n;j++)
            if(!vis[j][0] && tmp>dis[j][0]){
                k=j;
                flag=0;
                tmp=dis[j][0];
            }else if(!vis[j][1] && tmp>dis[j][1]){
                k=j;
                flag=1;
                tmp=dis[j][1];
            }
        if(tmp==INF)    //如果最短路和次短路都不存在，则退出for循环
            break;
        vis[k][flag]=true;
        for(j=head[k];j!=-1;j=edge[j].nxt){ //更新和点k相连的边
            int v=edge[j].to;
            if(dis[v][0]>tmp+edge[j].cap){  //比最短路短
                dis[v][1]=dis[v][0];
                count[v][1]=count[v][0];
                dis[v][0]=tmp+edge[j].cap;
                count[v][0]=count[k][flag];
            }else if(dis[v][0]==tmp+edge[j].cap){   // 等于最短路
                count[v][0]+=count[k][flag];
            }else if(dis[v][1]>tmp+edge[j].cap){    // 比次短路短
                dis[v][1]=tmp+edge[j].cap;
                count[v][1]=count[k][flag];
            }else if(dis[v][1]==tmp+edge[j].cap){   // 等于次短路
                count[v][1]+=count[k][flag];
            }
        }
    }
    if(dis[des][1]==dis[des][0]+1)
        count[des][0]+=count[des][1];
    printf("%d\n",count[des][0]);
}