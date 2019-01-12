#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
char str[maxn];
int cnt[30];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    int n;
    while(scanf("%d",&n)==1){
        scanf("%s",str+1);
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;++i){
            int c = str[i]-'a';
            cnt[c]++;
        }
        int one = 0, more = 0,tot=0;
        for(int i=0;i<26;++i){
            if(cnt[i]==0) continue;
            else if(cnt[i]==1) one++;
            else more++;
            tot++;
        }
        if(tot==1) printf("Yes\n");
        else if(more==0) printf("No\n");
        else printf("Yes\n"); 
    }
    return 0;
}