#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
struct Segment{
    int sta;
}vs[maxn];
int res;
int N;
int dfs(int d,int x)
{
    if(d==N){
        if(!vs[d].sta) return 1;
        else if(vs[d].sta==1){
            if(x==1) return 1;
            else return 0;
        }
        else if(vs[d].sta==2){
            if(x==2) return 1;
            else return 0;
        }
        else return 0;
    }
    if(!vs[d].sta){
        return 1+dfs(d+1,0);
    }
    else if(vs[d].sta==1){
        if(x==1) return 1+dfs(d+1,0);
        else return dfs(d+1,1);
    }
    else if(vs[d].sta==2){
        if(x==2) return 1+dfs(d+1,0);
        else return dfs(d+1,2);
    }
    else{
        if(x==0) return min(dfs(d+1,1),dfs(d+1,2));
        else if(x==1) return dfs(d+1,2);
        else return dfs(d+1,1);
    }
}

int main(){
    int T,M,num,t,x;
    int L,R;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d",&N)==1){
        int res=0;
        int pre=0;
        bool flag = true;
        int tmp=0;
        for(int i=1;i<=N;++i){
            scanf("%d",&vs[i].sta);
            if(pre && vs[i].sta) flag=false;
            if(!vs[i].sta)  tmp++;
            else{
                res+=tmp;
                tmp=0;
            }
            pre= vs[i].sta;
        }      
        res+=tmp;
        if(flag){
            printf("%d\n",res);
            continue;
        }
        int ans = dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}