#include<bits/stdc++.h>
typedef long long LL;
const int MAXN=6e5+5;
const int MOD=119 << 23 | 1;//998244353 1004535809
using namespace std;
vector<LL> conv;
void debug(){for(int i=0;i<conv.size();++i) cout<<conv[i]<<" "; cout<<endl;}
int n,m;
int len,s;
LL a[MAXN],b[MAXN],x[MAXN],y[MAXN];
LL wn[25];
LL Mul(LL x,LL y)//乘法超LL用快速乘，主函数也需要用
{
    LL ans=(x*y-(LL)((long double)x/MOD*y+1e-8)*MOD);
    return ans<0?ans+MOD:ans;
}
LL Qpow(LL a,LL b,LL M)
{
    LL ans=1;a%=M;
    while(b){
        if(b&1) ans=ans*a%MOD;
        a= a*a %MOD;
        b>>=1;
    }
    return ans;
}
void Getwn()//主函数预处理getwn()
{
    for(int i=0;i<25;i++){
        wn[i]=Qpow(3,(MOD-1)/(1<<i),MOD);
    }
}

void NTT(LL *x,int n,int rev)
{
    int i,j,k,ds;
    LL w,u,v;
    for(i=1,j=n>>1,k=n>>1;i<n-1;i++,k=n>>1){
        if(i<j) swap(x[i],x[j]);
        while(j>=k) j-=k,k>>=1;
        if(j<k) j+=k;
    }
    for(i=2,ds=1;i<=n;i<<=1,ds++){
        for(j=0;j<n;j+=i){
            w=1;
            for(k=j;k<j+i/2;k++){
                u=x[k];
                v = w*x[k+i/2]%MOD;
                //v=Mul(w,x[k+i/2]);
                x[k]=(u+v)%MOD;
                x[k+i/2]=(u-v+MOD)%MOD;
                w = w*wn[ds]%MOD;
                //w=Mul(w,wn[ds]);
            }
        }
    }
    if(rev==-1){
        for(i=1;i<n/2;i++) swap(x[i],x[n-i]);
        w=Qpow(n,MOD-2,MOD);
        for(i=0;i<n;i++) //x[i]=Mul(x[i],w);
            x[i] = x[i]*w%MOD;
    }
}

void getConv()
{
    int len=1,s=n+m;
    while(len<s) len<<=1;
    for(int i=n;i<len;i++) a[i]=0;
    for(int i=m;i<len;i++) b[i]=0;
    NTT(a,len,1); NTT(b,len,1);
    for(int i=0;i<len;i++)
        a[i] = a[i] *b[i]%MOD;//a[i]=Mul(a[i],b[i]);
    NTT(a,len,-1);
    conv.clear();
    for(int i=0;i<=s-2;++i){
        conv.push_back(a[i]%MOD);
    }
}

