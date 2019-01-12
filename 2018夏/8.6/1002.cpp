#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =10;
const LL INF= (1LL)<<60;
int k,len;
int pos[maxn];
int num[maxn];
bool vis[maxn];

int check(){
    memset(vis,0,sizeof(vis));
    int cnt =0;
    for(int i=0;i<len;++i){
        if(vis[i]) continue;
        int tmp=0;
        while(!vis[i]){
            tmp++;
            vis[i]=1;
            i = pos[i];
        }
        cnt += tmp-1;
        if(cnt>k) return 0;
    }
    return cnt;
}


char str[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    scanf("%d",&T);
    while(T--){
        memset(str,0,sizeof(str));
        scanf("%s %d",str,&k);
        len = strlen(str);
        LL N=0;
        for(int i=0;i<len;++i) num[i] = str[i]-'0',pos[i]=i,N = N*10+num[i];
        LL ans1= N,ans2=N;
        do{
            if(num[pos[0]]!=0 && check()){
                LL tmp =0;
                for(int i=0;i<len;++i){
                    tmp*=10;
                    tmp+= num[pos[i]];
                }
                if(tmp<ans1) ans1=tmp;
                if(tmp>ans2) ans2=tmp;
            }
        }while(next_permutation(pos,pos+len));
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}