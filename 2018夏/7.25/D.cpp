#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
bool vis[maxn];
int cnt[maxn];

bool isprime(int n)
{
    int limit = sqrt(n)+1;
    for(int i=2;i<limit;++i)
        if(n%i==0)  return false;
    return true;
}

int main(){
    int T,n,m,num,t,x;
    cin>>T;
    while(T--){
        memset(vis,0,sizeof(vis));
        memset(cnt,0,sizeof(cnt));
        scanf("%d%d",&n,&m);
        queue<int> q;
        q.push(n);
        while(!q.empty()){
            num=q.front(); q.pop();
            if(num==m) break;
            vis[num]=true;      //已访问
            x = num;            //保存num
            int a[5],pos=0;
            while(num){
                a[pos++]=num%10;
                num/=10;
            }
            for(int i=0;i<=9;++i){
                for(int j=0;j<4;++j){
                    if(j==3&&i==0)continue;
                    if(j==0)    num = i+a[1]*10+a[2]*100+a[3]*1000;
                    if(j==1)    num = a[0]+i*10+a[2]*100+a[3]*1000;
                    if(j==2)    num = a[0]+a[1]*10+i*100+a[3]*1000;
                    if(j==3)    num = a[0]+a[1]*10+a[2]*100+i*1000;

                    if(vis[num] == false&& isprime(num) == true){
                            vis[num] = true;
                            cnt[num] = cnt[x]+1;
                            q.push(num);
                    }
                }
            }
        }
        if(n==m || cnt[m])
            printf("%d\n",cnt[m]);
        else printf("Impossible\n");
    }
    return 0;
}