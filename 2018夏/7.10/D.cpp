#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5,maxc = 2e6+5;
int step[maxc];


int main()
{
    int N,K,x;
    string num;
    while(scanf("%d%d",&N,&K)==2){
        memset(step,-1,sizeof(step));
        string str;
        queue<int> Q;
        for(int i=1;i<=N;++i){
            int num=0;
            cin>>str;
            for(int j=0;j<K;++j){
                if(str[j]=='1')
                    num|=(1<<j);
            }
            step[num] =0;   
            Q.push(num);
        }
        int t,mxstep=-1,res;
        while(!Q.empty()){
            x = Q.front(); Q.pop();
            for(int i=0;i<K;++i){
                t= x^(1<<i);
                if(step[t]!=-1) continue;
                step[t] =step[x]+1;
                Q.push(t);
                if(mxstep<step[t]){
                    mxstep=  step[t];
                    res = t;
                }      
            }
        }
        for(int i=0;i<K;++i){
            printf("%d",res&1);
            res>>=1;
        }
        printf("\n");
    }
    return 0;
}