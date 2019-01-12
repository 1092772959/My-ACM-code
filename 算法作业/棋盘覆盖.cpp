#include<bits/stdc++.h>
using namespace std;
const int maxn = 105;
int board[maxn][maxn];
int num,k,cas=1;


void dfs(int sx, int sy, int dx, int dy, int size)
{ //(sx,sy)为该方阵的左上角坐标，(dx,dy)是这个方针中被覆盖的点坐标
  if(size==1) return;
  int nump = num++, s = size/2;
  if(dx <= sx +s -1 && dy <= sy+s-1){   //非法点在左上部分
    dfs(sx,sy,dx,dy,s);
  }
  else{
    board[sx+s-1][sy+s-1] = nump;      //否则用覆盖其右下角
    dfs(sx,sy,sx+s-1,sy+s-1, s);
  }
  if(dx<=sx+s-1 && dy>=sy+s){           //在右上部分
    dfs(sx,sy+s,dx,dy,s);
  }
  else{                                //否则覆盖其左下角
    board[sx+s-1][sy+s] = nump; 
    dfs(sx,sy+s,sx+s,sy+s-1,s);
  }
  if(dx>=sx+s && dy<= sy+s-1){        //在左下部分
    dfs(sx+s,sy,dx,dy,s);  
  }
  else{                               //否则覆盖右上部分
    board[sx+s][sy+s-1] = nump;
    dfs(sx+s,sy,sx+s,sy+s-1,s);
  }
  if(dx>=sx+s && dy>= sy+s){          //在右下部份
    dfs(sx+s,sy+s,dx,dy,s);
  }
  else{                               //否则覆盖左上部分
    board[sx+s][sy+s] = nump;
    dfs(sx+s,sy+s,sx+s,sy+s,s);
  }
}

void show()     //输出函数
{
  int n = 1<<k;
  printf("Case %d: n=%d\n",cas++,n);
  for(int i=1;i<=n;++i){
    for(int j = 1;j<=n;++j){
      cout.width(3);
      if(board[i][j]) cout<<board[i][j];
      else cout<<"#";
    }
    puts("");
  }
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
  #endif
  int tx,ty;
  cout<<"谢谢";
  while(scanf("%d %d %d",&k,&tx,&ty)==3){
    memset(board,0,sizeof(board));
    num = 1;
    int sz = 1<<k;
    dfs(1,1,tx,ty,sz);
    show();
    int n,m;
    scanf("%d %d",&n, &m);
  }
  return 0;  
}