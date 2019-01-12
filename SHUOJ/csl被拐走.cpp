#include<iostream>
#include<cstring>
#include<stdio.h>
#include<map>
#include<string>
#include<algorithm>
#include<queue>
#define LOCAL
using namespace std;
typedef double LL;
const int maxn =100;
struct Node{
    int x,y,step;  
};

int L,R,C;
char G[maxn][maxn];
int dir[4][2]={1,0,-1,0,0,1,0,-1};
bool check(Node & p)
{
    if(p.x<1||p.x>R || p.y<1||p.y>C) return false;
    else if(G[p.x][p.y]=='#') return false;
    else return true;
}

int BFS(int r,int c)
{
    Node s;
    queue<Node> Q;
    s.x=r,s.y=c,s.step=0;
    Q.push(s);
    G[r][c]='#';
    while(!Q.empty()){
        Node p = Q.front();Q.pop();
        if(!check(p)) continue;
        if(G[p.x][p.y]='E') return p.step;
        G[p.x][p.y]='#';
        for(int i=0;i<4;++i){
            Q.push((Node){p.x+dir[i][0],p.y+dir[i][1],p.step+1});
        }
    }
    return -1;
}

int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    char op[50];
    int sx,sy;
    while(scanf("%d%d%d",&L,&R,&C)==3,L&&R&&C){
        int res=0;
        for(int k=1;k<=L;++k){
            for(int i=1;i<=R;++i){
                scanf("\n%s",op);
                for(int j=1;j<=C;++j){
                    if(op[j-1]=='S'){
                        sx = i,sy=j;
                    }
                    else G[i][j]= op[j-1];
                }
            }
            res+=BFS(sx,sy);
        }
    
        int res=BFS(sx,sy);
        if(res==-1) printf("Trapped!\n");
        else printf("Escaped in %d minute(s).\n",res);
    }
    return 0;
}