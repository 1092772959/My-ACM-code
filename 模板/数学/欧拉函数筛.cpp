#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1100005;
int phi[maxn];              //欧拉函数
int res[maxn];              //res[i]:求最小的满足phi[x]>=i的X
bool isprime[maxn];

void Euler()
{             //欧拉函数表
    for(int i=1;i<maxn;++i) phi[i] = i;
    memset(isprime,1,sizeof(isprime));
    isprime[0] = isprime[1] = false;
    phi[1] =0;
    for(int i=2;i<maxn;++i){
        if(!isprime[i]) continue;
        for(int j=i;j<maxn;j+=i){
            isprime[j] = false;
            phi[j] -= phi[j]/i;
        }
    }
}

void pre()
{
    memset(res,0,sizeof(res));
    for(int i=1;i<maxn;++i){
        for(int j=phi[i];j>=0 && res[j]==0;--j){
            res[j] = i;
        }
    }
}