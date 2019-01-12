#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn =10;
int dir[8][2]={-2,1,-1,2,1,2,2,1,-2,-1,-1,-2,1,-2,2,-1};
struct Node{
    int x,y,step;
};
bool vis[maxn][maxn];
int color[maxn][maxn];
int ex,ey;
bool check(int i,int j)
{
    if(i<1 || i>8 ||j<1||j>8) return false;
    else if(vis[i][j]) return false;
    return true;
}

int BFS(int sx,int sy)
{
    memset(vis,0,sizeof(vis));
    queue<Node> Q;
    Q.push((Node){sx,sy,0});
    vis[sx][sy]=true;
    while(!Q.empty()){
        Node p = Q.front();Q.pop();
        if(p.x ==ex && p.y ==ey) return p.step;
        for(int i=0;i<8;++i){
            int nx = p.x +dir[i][0];
            int ny = p.y +dir[i][1];
            if(check(nx,ny)){
                Q.push((Node){nx,ny,p.step+1});
                vis[nx][ny]=1;
            }
        }
    }
    return -1;    
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    char st[5],ed[5];
    while(scanf("%s",st)==1){
        scanf("%s",ed);
        int sx = st[0]-'a'+1,sy =st[1]-'0';
        ex = ed[0]-'a'+1,ey=ed[1]-'0';
        printf("To get from %s to %s takes %d knight moves.\n",st,ed,BFS(sx,sy));
    }    
    return 0;
}
/*
#include<stdio.h>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char ss[3];
char ee[3];
struct node{
    int x,y;
};
int d[8][2]={{-2,1},{-2,-1},{-1,-2},{-1,2},{2,-1},{2,1},{1,-2},{1,2}};
int visited[8][8];
int color[8][8];
node s;
node e;
int in(node n)
{
    if(n.x<0||n.y<0||n.x>7||n.y>7) return 0;
    return 1;
}
int bfs()
{
    queue<node>qf;                     
    queue<node>qb;
    memset(visited,0,sizeof(visited));
    memset(color,0,sizeof(color));
    qf.push(s);
    qb.push(e);
    visited[e.x][e.y]=1;
    color[s.x][s.y]=1;
    color[e.x][e.y]=2;
    while(!qf.empty()||!qb.empty()){
        if(!qf.empty()){
            node st=qf.front();
            qf.pop();
            for(int i=0;i<8;++i){
                node t;
                t.x=st.x+d[i][0];
                t.y=st.y+d[i][1];
                if(in(t)){
                    if(color[t.x][t.y]==0){
                        visited[t.x][t.y]=visited[st.x][st.y]+1;
                        color[t.x][t.y]=1;
                        qf.push(t);
                    }
                    else if(color[t.x][t.y]==2)
                        return visited[st.x][st.y]+visited[t.x][t.y];
                }
            }

        }
        if(!qb.empty()){
            node st=qb.front(); qb.pop();
            for(int i=0;i<8;++i){
                node t;
                t.x=st.x+d[i][0];
                t.y=st.y+d[i][1];
                if(in(t)) {
                    if(color[t.x][t.y]==0){
                        visited[t.x][t.y]=visited[st.x][st.y]+1;
                        color[t.x][t.y]=2;
                        qb.push(t);
                    }
                    else if(color[t.x][t.y]==1)
                        return visited[st.x][st.y]+visited[t.x][t.y];
                }
            }
        }
    }
}
int main(int argc, char *argv[])
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    while(scanf("%s %s",ss,ee)==2){
        s.x=ss[0]-'a';
        s.y=ss[1]-'1';
        e.x=ee[0]-'a';
        e.y=ee[1]-'1';
        if(s.x==e.x&&s.y==e.y) printf("To get from %s to %s takes 0 knight moves.\n",ss,ee);
        else printf("To get from %s to %s takes %d knight moves.\n",ss,ee,bfs());
    }
    return 0;
}
*/