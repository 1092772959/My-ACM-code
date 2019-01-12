#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn  =1e5+5;
const int mod = 1e9+7;
#define X first
#define Y second
typedef pair<int,int> PII;
const int SIZE = 3;
struct Matrix
{
    int n,m;
    LL ma[5][5];
    Matrix (int x,int y):n(x),m(y){clear();}
    void set(int n_,int m_){n = n_,m = m_;}
    LL *operator[](int x){return ma[x];}
    Matrix operator*(Matrix x){
        Matrix res(n,x.m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=x.m;j++)
                for(int k=1;k<=m;k++)
                    (res[i][j]+=ma[i][k]*x[k][j]%mod+mod)%=mod;
        return res;
    }
    Matrix operator ^(int y){
        Matrix x(n,m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                x[i][j]=ma[i][j];
        Matrix res(x.n,x.n);
        for(int i=1;i<=x.n;i++)
            res[i][i]=1;
        for(;y;y>>=1,x=x*x)
            if(y&1)res=res*x;
        return res;
    }
    void print(){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                printf("%lld%c",ma[i][j]," \n"[j==m]);
    }
    void clear(){memset(ma,0,sizeof(ma));}
};

int P,n;
PII f(int x,int y){
    if(!x)return make_pair(y,n+1);
    int l = y ,r = min(n,P/x);
    return make_pair(l,r+1);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N;
    scanf("%d",&T);
    while(T--){
        int A,B,C,D;
        scanf("%d%d%d%d%d%d",&A,&B,&C,&D,&P,&n);
        if(n<=2){
            if(n==1) printf("%d\n",A);
            else if(n==2) printf("%d\n",B);
            continue;
        }
        vector<PII> kuai;
        for(int i=3;i<=n;){
            PII seg =f(P/i,i);
            kuai.push_back(seg);
            i = seg.Y;   
        }
        Matrix x(1,3),y(3,3);
        x[1][1] = B,x[1][2]=A,x[1][3]=1;
        for(int i=3;i<=n;){
            PII seg = f(P/i,i);
            y[1][1]=D,y[1][2] = 1,y[1][3] = 0;
            y[2][1]=C,y[2][2] = 0,y[2][3] = 0;
            y[3][1]=P/i,y[3][2]=0,y[3][3] = 1;
            x = x*(y^(seg.Y - seg.X));
            i = seg.Y;
        }
        printf("%lld\n",x[1][1] );
    }
    return 0;
}