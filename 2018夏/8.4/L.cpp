#include<stdio.h>
#include<cstring>
#include<iostream>
#include<stack>
using namespace std;
typedef long long LL;
const int maxn =1e6+5;
const int INF=0x3f3f3f3f;
const LL mod = 1e9+7;
bool vis[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,u,v,tmp,T;
    char str[maxn];
    while(~scanf("%s",str)){
        int res=0,cnt=0;
        memset(vis,0,sizeof(vis));
        int len = strlen(str);
        int tmp=0;
        for(int i=0;i<len;++i){
            int c =str[i];
            if(c=='(') tmp++;
            else{
                if(tmp) vis[i] =true;
                tmp--;
            }
            tmp=max(tmp,0);
        }
        tmp=0;
        for(int i=len-1;i>=0;i--){
            char c = str[i];
            if(c==')') tmp++;
            else{
                if(tmp) vis[i]=true;
                tmp--;
            }
            tmp=max(tmp,0);
        }
        tmp=0;
        for(int i=0;i<len;++i){
            if(vis[i])
                tmp++;
            else tmp=0;
            
                if(tmp==res) cnt++;
                else if(tmp>res){
                    cnt=1;
                    res=tmp;
                }
            
        }
        if(!res) puts("0 1");
        else printf("%d %d\n",res,cnt);
    }
    return 0;
}