#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int st[maxn][15];           //do记录大小,pos记录下标
int h[maxn];
int prev[maxn];
int c[maxn];
bool inc[maxn];
int dp[maxn];
int N;

void ST()
{  
    for(int i=1;i<=N;++i) st[i][0] = h[i]; 
    for(int j=1;(1<<j)<=N;++j){
        for(int i=1;i+(1<<j)<=N+1;++i){
            st[i][j] = max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}

int RMQ(int L,int R)
{
    int k=0;
    while((1<<(k+1))<=R-L+1) k++;
    if(st[L][k]>st[R-(1<<k)+1][k])  return st[L][k];
    else return st[R-(1<<k)+1][k];
}

/*
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200007;
int N, m, tot;
int h[200005];
int st[MAXN][32-__builtin_clz(MAXN)];
int dp[200005];
int sel[200005], pre[200005], c[200005];

void init_st() {
  int l = 31 - __builtin_clz(N);
  for(int i=0;i<N;++i) st[i][0] = h[i];
  for(int j=0;j<l;++j) 
    for (int i=0;i<1+N-(1<<j);++i)
        st[i][j+1] = max(st[i][j], st[i+(1<<j)][j]);
}

int rmq(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  return max(st[l][k], st[r-(1<<k)+1][k]);
}

*/