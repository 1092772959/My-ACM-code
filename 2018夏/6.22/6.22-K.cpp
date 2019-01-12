#include<bits/stdc++.h>
using namespace std;

const int maxn =100;
int d[maxn],w[maxn];
int D,W;
queue<int> q1,q2;

int solve()
{
    int res=0;
    int e1,e2;
    while(!q1.empty()){
        e1=q1.front();q1.pop();
        int cnt = q2.size();
        while(!q2.empty()&& cnt){
            e2=q2.front();q2.pop();
            if(e1==e2){
                res+=e1;
                break;
            }
            cnt--;                      //尝试次数
            q2.push(e2);
        }
        if(!cnt) res+=e1;
    }
    
    while(!q2.empty()){
        e2 = q2.front(); q2.pop();
        res+=e2;
    }
    return res;
}


int main()
{
    while(~scanf("%d%d",&W,&D),W+D){
        for(int i=1;i<=W;++i){
            scanf("%d",&w[i]);
            q1.push(w[i]);
        }
        for(int i=1;i<=D;++i){
            scanf("%d",&d[i]);
            q2.push(d[i]);
        }
        printf("%d\n",solve());
    }
    return 0;
}