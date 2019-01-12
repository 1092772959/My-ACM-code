#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAX_L 2005 //最大长度，可以修改
const int maxn = 1e5+5;
char op[maxn];
int main(){
    int T,M,num,t,x,cas=1;
    int N;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    scanf("%d",&T);
    LL b;
    while(T--){
        scanf("%s %lld",op,&b);
        LL re =0;
        if(b<0) b=-b;
        int len = strlen(op);
        LL num=0;
        for(int i=0;i<len;++i){
            if(op[i]=='-') continue;
            num = (num*10+(op[i]-'0'))%b;
        }
        printf("Case %d: ",cas++);
        if(num==0) printf("divisible\n");
        else printf("not divisible\n");
    }
    return 0;
}