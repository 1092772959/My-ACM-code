#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int mod = 7901;
#define PI 3.1415926
#define eps 1e-10
int cnt1[30],cnt2[30];

//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int T,N;
    scanf("%d",&T);
    while(T--){
        memset(cnt1,0,sizeof(cnt1));
        memset(cnt2,0,sizeof(cnt2));
        char s1[maxn],s2[maxn];
        scanf("\n%s",&s1);
        scanf("\n%s",&s2);
        int len = strlen(s1);
        int a,b,res=0;
        int limit = len/2;
        int flag = 0;
        for(int i=0;i<=limit;++i){
            if(flag)  swap(s1[i],s1[len-i-1]);
            if(s1[i]==s2[i] && s1[len-i-1]==s2[len-i-1]) continue;
            else if(s1[i]==s2[len-i-1] && s1[len-i-1] == s2[i]) {
                res++;
                flag ^=1;
            }
            else{
                res=-1;
                break;
            }
        }
        printf("%d\n",res);
    }    
    return 0;
}