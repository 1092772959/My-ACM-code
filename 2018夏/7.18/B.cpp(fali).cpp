#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 50005;
char nstr[maxn];
char str[maxn*3];
int cnt [30];
#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,s,t,u,v,T;
    LL tmp,b;
    while(scanf("%d",&N)==1){
        memset(str,0,sizeof(str));
        memset(cnt,0,sizeof(cnt));
        scanf("%s",str);
        int len = strlen(str),nlen = len*3-2;
        for(int i=0;i<len-1;i++){
            nstr[i]=str[i+1];
        }
        for(int i=len-1;i<2*len-1;++i){
            nstr[i]=str[i-len+1];
        }
        for(int i=2*len-1;i<nlen;++i){
            nstr[i]=str[i-2*len+1];
        }
        for(int i=0;i<len;++i) cnt[str[i]-'a']++;
        bool flag = false;
        LL res = 0;
         for(int i = 0; i < nlen; ++i){
            for(int j = i+1; j <nlen; ++j){
                flag = true;
                for(int k = 0; k < (j - i + 1)/2; ++k){
                    if(nstr[i] != nstr[j - k])
                        flag = false;
                }
                if(flag){
                    res++;
                }
            }
        }
        for(int i=0;i<26;++i){
            if(cnt[i]>1) res+=cnt[i]-1;
        }
        printf("%lld\n",N+2*N*(N-1)-res);
    }  
    return 0;
}
