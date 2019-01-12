#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAXN 1010  
#define MAXM 1000000+10  
#define INF 0x3f3f3f3f  
using namespace std;  
struct Edge  {  
    int from, to,cost;  
};  
Edge edge[MAXM];  
int pre[MAXN];//存储父节点  
int vis[MAXN];//标记作用  
int id[MAXN];//id[i]记录节点i所在环的编号  
int in[MAXN];//in[i]记录i入边中最小的权值  
int point;
LL zhuliu(int root, int n, int m)//root根 n点数 m边数  
{  
    LL res=0;
    int  u, v;  
    while(true){  
        for(int i = 0; i < n; i++)  
            in[i] = INF;//初始化  
        for(int i = 0; i < m; i++){  
            Edge E = edge[i];  
            if(E.from != E.to && E.cost < in[E.to]){  
                pre[E.to] = E.from;//记录前驱  
                in[E.to] = E.cost;//更新  
                if(E.from == root){     //模板中的修改
                    point = i;        
                }
            }  
        }  
        for(int i = 0; i < n; i++)  
            if(i != root && in[i] == INF)  
                return -1;//有其他孤立点 则不存在最小树形图  
        int tn = 0;//记录当前查找中 环的总数  
        memset(id, -1, sizeof(id));  
        memset(vis, -1, sizeof(vis));  
        in[root] = 0; 
        for(int i = 0; i < n; i++){  
            res += in[i];
            v = i;  
            while(vis[v] != i && id[v] == -1 && v != root){  
                vis[v] = i; 
                v = pre[v];
            }  
            if(v != root && id[v] == -1)//必须上述查找已经找到有向环  
            {  
                for(int u = pre[v]; u != v; u = pre[u])  
                    id[u] = tn;//记录节点所属的 环编号  
                id[v] = tn++;//记录节点所属的 环编号  环编号累加  
            }  
        }  
        if(tn == 0) break;//不存在有向环  
        for(int i = 0; i < n; i++)  
            if(id[i] == -1)  
                id[i] = tn++;
        for(int i = 0; i < m; i++)  {  
            v = edge[i].to;  
            edge[i].from = id[edge[i].from];  
            edge[i].to = id[edge[i].to];  
            if(edge[i].from != edge[i].to)  
                edge[i].cost -= in[v];//更新边权值 继续下一条边的判定  
        }  
        n = tn;
        root = id[root];  
    }  
    return res;  
}  

int main()
{
    int T,N,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        int sum=0;
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            edge[i].from=u+1;
            edge[i].to = v+1;
            edge[i].cost = tmp;
            sum+=tmp;    
        }
        sum++;
        for(int i = M ; i < N + M ; i++) {
            edge[i].from = 0;   
            edge[i].to = i - M + 1;
            edge[i].cost = sum;
        }
        LL res = zhuliu(0,N+1,N+M);
        if(res==-1 || res>=sum*2) printf("impossible\n");
        else printf("%lld %d\n",res-sum, point-M);
        printf("\n");
    }
    return 0;
}