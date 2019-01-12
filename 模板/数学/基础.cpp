#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000007,maxn=10000000;
int n,m;

int gcd(int a,int b)            //公约数
{
    if(b==0) return a;
    return gcd(b,a%b);
}

int extgcd(int a,int b,int & x,int & y)         //扩展欧几里得
{
    int d=a;
    if(b!=0){
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
        x=1,y=0;
    return d;
}

map<int,int> prime_factor(int n)            //分解质因数
{
    map<int,int> res;
    for(int i=2;i*i<=n;++i){
        while(n%i==0){
            ++res[i];
            n/=i;
        }
    }
    if(n!=1) res[n]=1;
    return res;
}

vector<int> divisor(int n)                      //约数枚举
{
    vector<int> res;
    for(int i=1;i*i<=n;++i){
        if(n%i==0){
            res.push_back(i);
            if(i!=n/i) res.push_back(n/i);
        }
    }
    return res;
}

bool isprime(int n)                //素数判定
{
    if(n==1) return false;
    for(int i=2;i*i<=n;++i){
        if(n%i==0)  return false;
    }
    return true;
}

int prime[maxn];
bool is_prime[maxn];

int sieve(int n)                            //埃氏筛法，求n以内素数的个数
{
    int p=0;
    for(int i=0;i<=n;++i)  is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;++i){
        if(is_prime[i]){
            prime[p++]=i;
            for(int j=2*i;j<=n;j+=i)
                is_prime[j]=false;
        }
    }
    return p;
}

int mod_inverse(int a,int m)
{	//求逆元
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}

//线性方程组
pair<int,int> linear_congruence(const vector<int>& A,const vector<int>& B,const vector<int>& M)
{
    int x=0,m=1;
    for(int i=0;i<A.size();++i){
        int a=A[i]*m,b=B[i]-A[i]*x,d=gcd(M[i],a);
        if(b%d!=0)
            return make_pair(0,-1);
        int t=b/d*mod_inverse(a/d,M[i]/d)%(M[i]/d);
        x=x+m*t;
        m*=M[i]/d;
    }
    return make_pair(x%m,m);
}
