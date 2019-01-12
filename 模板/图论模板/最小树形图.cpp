#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<cmath>
using namespace std;
const int maxn = 1e2+5;
const double INF = 1<<18;
bool vis[maxn],flag[maxn];
int n,m,pre[maxn];
double w[maxn][maxn];

pair<int,int> P[maxn];

double Dist(int i,int j){
    return sqrt((P[i].first-P[j].first)*(P[i].first-P[j].first)+(P[i].second-P[j].second)*(P[i].second-P[j].second));
}

void init()//不能少了初始化的内容
{
    memset(vis, 0, sizeof(vis));
    memset(flag, 0, sizeof(flag));
    for(int i=0; i<=n; i++){
        w[i][i] = INF;
        for(int j=i+1; j<=n; j++)
            w[i][j]=w[j][i]=INF;
    }
}

double directed_mst(int u)//u表示根节点
{
    double ans=0;
    memset(vis, 0, sizeof(vis));
    while(true){
        //求最短弧集合E
        for(int i=1; i<=n; i++){
            if(i!=u&&!flag[i]){
                w[i][i]=INF, pre[i] = i;
                for(int j=1; j<=n; j++)
                    if(!flag[j] && w[j][i]<w[pre[i]][i]){
                        pre[i] = j;
                    }
                if(pre[i]==i)return -1;//也可以用dfs预处理判断凸的连通
            }
        }
        //判断E是否有环
        int i;
        for(i=1; i<=n; i++){
            if(i!=u&&!flag[i]){
                int j=i, cnt=0;
                while(j!=u && pre[j]!=i && cnt<=n) j=pre[j], ++cnt;
                if(j==u || cnt>n) continue; //最后能找到起点（根）或者是走过的点已经超过了n个，表示没有有向环
                break;
            }
        }
        if(i>n){                //无环，返回结果
            for(int i=1; i<=n; i++)
                if(i!=u && !flag[i]) 
                    ans+=w[pre[i]][i];
            return ans;
        }
        //有环，进行收缩，把整个环都收缩到一个点i上。
        int j=i;
        memset(vis, 0, sizeof(vis));
        do{
            ans += w[pre[j]][j], j=pre[j], vis[j]=flag[j]=true;//对环内的点标记，并且直接对环的权值进行加和记录，在最后找到最小树形图之后就不用展开收缩点了
        }
        while(j!=i);
        flag[i] = false; // 环缩成了点i，点i仍然存在
        //收缩点的同时，对边权值进行改变
        for(int k=1; k<=n; ++k)
            if(vis[k])  // 在环中点点
            {
                for(int j=1; j<=n; j++)
                    if(!vis[j])   // 不在环中的点
                    {
                        if(w[i][j] > w[k][j]) 
                            w[i][j] = w[k][j];
                        if(w[j][k]<INF && w[j][k]-w[pre[k]][k] < w[j][i])
                            w[j][i] = w[j][k] - w[pre[k]][k];
                    }
            }
    }
    return ans;
}
