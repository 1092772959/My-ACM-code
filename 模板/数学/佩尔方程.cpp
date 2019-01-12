#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define mod 8191
#define N 2
typedef struct{
    int m[N][N];
}matrix;
matrix per,d;
int n;
int x,y,D;
void search()
{
    y=1;
    while(true)
    {
        x=(int)sqrt(D*y*y+1.0);
        if(x*x-D*y*y==1) break;
        y++;
    }
}
void init()
{
    d.m[0][0]=x%mod;
    d.m[0][1]=D*y%mod;
    d.m[1][0]=y%mod;
    d.m[1][1]=x%mod;
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        per.m[i][j]=(i==j);
}
matrix multi(matrix a,matrix b)
{
    matrix c;
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
      {
          c.m[i][j]=0;
          for(int k=0;k<N;k++)
            c.m[i][j]+=a.m[i][k]*b.m[k][j];
        c.m[i][j]%=mod;
      }
      return c;
}
matrix quick_mod(int k)
{
    matrix p=d,ans=per;
    while(k)
    {
        if(k&1)
        {
            ans=multi(ans,p);
            k--;
        }
        k>>=1;
        p=multi(p,p);
    }
    return ans;
}
int main()
{
    int K;
    while(cin>>D>>K)
    {
        int ad=(int)sqrt(D+0.0);
        if(ad*ad==D)
        {
            puts("No answer\n");
            continue;
        }
        search();
        init();
        d=quick_mod(K-1);

        int resx=(d.m[0][0]*x%mod+d.m[0][1]*y%mod)%mod;
        int resy=(d.m[1][0]*x%mod+d.m[0][0]*y%mod)%mod;
        printf("%d %d\n",resx,resy);

    }
    return 0;
}

//X(n+1) = x0*xn+d*y0*yn
//y(n+1) = y0*xn+x0*yn
