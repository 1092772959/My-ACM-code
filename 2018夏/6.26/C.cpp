#include<bits/stdc++.h>
using namespace std;
const int maxn =2e5+5;
const int INF = 0x3f3f3f3f;
int dir[4][2] ={-1,0,1,0,0,-1,0,1};
struct Node{
    int x,y;
    int step;
}G[maxn];
char Map[maxn];
int N,M,K;
Node tmp,s,t;
vector<Node> Mon;
char str[maxn];
bool FLAG;

bool check(int x,int y)
{
    if(x<0 ||x>=N||y<0 ||y>=M)
        return false;
    if(Map[x*M+y]=='M')
        return false;
    return true;
}

void pre()
{
    queue<Node> Q;
    Node p;
    int nx,ny,pos;
    for(int i=0;i<Mon.size();++i){
        Mon[i].step=0;
        Q.push(Mon[i]);
    }
    while(!Q.empty()){
        p = Q.front();Q.pop();
        if(p.step>=K)   continue;
        for(int i=0;i<4;++i){
            nx = p.x + dir[i][0];
            ny = p.y + dir[i][1];
            pos =nx*M+ny;                           //一维
            if(!check(nx,ny)) continue;
            else if(Map[pos]=='S' || Map[pos]=='F'){      //覆盖起点终点
                FLAG=false;
                return ;
            } 
            else{
                G[pos].step = p.step+1;
                Map[pos] = 'M';
                Q.push(G[pos]);
            }       
        }
    }
}

int  BFS()
{
    if(!FLAG) return -1;
    queue<Node> Q;
    Map[s.x*M+s.y]='M';
    G[s.x*M+s.y].step = 0;
    Q.push(G[s.x*M+s.y]);
    int nx,ny,pos;
    Node p;
    while(!Q.empty()){
        p =Q.front();Q.pop();
        if(p.x==t.x && p.y==t.y) 
            return p.step;       //找到终点
        for(int i=0;i<4;++i){
            nx = p.x + dir[i][0];
            ny = p.y + dir[i][1];
            pos =nx*M+ny;
            if(!check(nx,ny))   continue;
            else{
                G[pos].step = p.step+1;
                Map[pos] = 'M';
                Q.push(G[pos]);
            } 
        }
    }
    return -1;
}

int main()
{
    int pos;
    while(scanf("%d%d%d",&N,&M,&K)==3){
        Mon.clear();
        FLAG=true;
        for(int i=0;i<N;++i){
            scanf("%s",str);
            for(int j=0;j<M;++j){
                pos = i*M+j;
                Map[pos] = str[j];
                G[pos].x = i;
                G[pos].y = j;
                if(str[j]=='S') s=G[pos];
                else if(str[j]=='F')    t=G[pos];
                else if(str[j]=='M')    Mon.push_back(G[pos]);
                else;
            }
        }
        pre();

        printf("%d\n",BFS());
    }
    return 0;
}
