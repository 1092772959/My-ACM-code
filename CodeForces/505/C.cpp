#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long LL;
const int maxn =2e5+5;
char str[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(~scanf("%s",str)){
        int len = strlen(str);
        for(int i=0;i<len;++i) str[i+len] = str[i];
        int tot = len*2;
        int ans =0,cnt=1;
        for(int i=1;i<tot;++i){
            if(str[i-1]!=str[i]) cnt++;
            else cnt=1;
            ans = max(ans,min(len,cnt));
        }
        printf("%d\n",ans);
    }
    return 0;
}

