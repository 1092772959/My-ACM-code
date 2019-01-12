#include<bits/stdc++.h>
using namespace std;
const int maxn =55;
bool used[maxn][maxn];
int G[maxn][maxn];
int pre[maxn][maxn],DFN;
int dir[4][2]={-1,0,1,0,0,-1,0,1};
bool Fd;

int N,M;
bool check(int &x,int &y){
    if(x<1 || x>N || y<1 ||y>M)
        return false;
    return true;
}

void dfs(int x,int y){
    if(Fd==true)    
        return;
    used[x][y]=true;
    pre[x][y]  = ++DFN;
    int nx,ny;
    for(int i =0;i<4;++i){
        nx = x+dir[i][0];
        ny = y+dir[i][1];
        if(!check(nx,ny) || G[nx][ny]!=G[x][y])     //不符合条件
            continue;
        if(!used[nx][ny]){
            dfs(nx,ny);
            DFN = pre[x][y];
        }
        else{           //找到祖先
            if(pre[nx][ny]+3<=pre[x][y])
                Fd=true;
        }   
    }
}

int main()
{
    char str[60];
    while(scanf("%d%d",&N,&M)==2){
        memset(used,0,sizeof(used));
        for(int i=1;i<=N;++i){
            cin>>str;
            for(int j=1;j<=M;++j){
                G[i][j]=str[j-1]-'A';
            }
        }
        DFN=0;
        Fd=false;
        for(int i=1;i<=N&&!Fd;++i){
            for(int j=1;j<=M && !Fd;++j){
                if(!used[i][j]){
                    dfs(i,j);
                }
            }
        }
        if(Fd)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;  
    }
    return 0;
}
