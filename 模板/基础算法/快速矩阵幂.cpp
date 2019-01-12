#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9+7;
typedef vector<LL> vec;
typedef vector<vec> mat;

mat mul(mat &a, mat &b)
{
	mat c(a.size(), vec(b[0].size()));
	for (int i = 0; i<a.size(); i++){
		for (int j = 0; j<b.size(); j++){
			for (int k = 0; k<b[0].size(); k++){
				c[i][j] += (a[i][k] * b[k][j])%mod;
				c[i][j] = (c[i][j]%mod+mod)%mod;
			}
		}
	}
	return c;
}
mat pow(mat a, LL n)
{
	mat res(a.size(), vec(a.size()));
	for (int i = 0; i<a.size(); i++)
		res[i][i] = 1;
	while (n){
		if (n & 1) res = mul(res, a);
		a = mul(a, a);
		n >>=1;
	}
	return res;
}

LL solve(LL n)
{
    int Size = 2;
    mat M(Size,vec(Size));
    M[0][0]=3,M[0][1]=-1,M[1][0]=1,M[1][1]=0;
    M=pow(M,n-1);
    LL res=M[0][0];
    return res;
}



/*
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
*/