#include<bits/stdc++.h>
using namespace std;
vector<int> p;

void facto(int num)
{
    int tmp=num;
    for(int i=2;i*i<=num;++i){
        if(tmp%i==0){
            p.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp>1)   p.push_back(tmp);
}

int main()
{
    int N,M,T=1;
    while(~scanf("%d%d",&N,&M)){
        p.clear();
        facto(M);
        int ans=0,L = p.size();
        for(int i=1;i<(1<<L);++i){
            int cnt =0,t=1;
            for(int j=0;j<L;++j){
                if((1<<j)&i){
                    t*=p[j];
                    cnt++;
                }
            }
            if(cnt&1)   ans+=N/t;
            else ans-=N/t;
        }
        printf("Case %d: %d\n",T++,N-ans);    
    }
    return 0;
}

