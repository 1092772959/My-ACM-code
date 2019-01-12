#include<bits/stdc++.h>
using namespace std;
vector <int> P;
const int INF=0x3f3f3f3f;

int gcd(int a,int b)    {return b==0? a:gcd(b,a%b);}

void facto(int N)               //质因子分解
{
    P.clear();
    int tmp =N;
    for(int i=2;i*i<=N;++i){
        if(tmp%i==0){
            P.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp>1) P.push_back(tmp);
}

int CNT(int N)      //1-N中与p互质的个数
{
    int ans=0,L = P.size();
    for(int i=1;i<(1<<L);++i){
        int cnt =0,t=1;
        for(int j=0;j<L;++j){
            if((1<<j)&i){
                t*=P[j];
                cnt++;
            }
        }
        if(cnt&1)   ans+=N/t;
        else ans-=N/t;
    }
    return N-ans;
}
