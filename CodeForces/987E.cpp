#include<iostream>
#include<stdio.h>
#include<cstring>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn = 1e6+5;
LL bit[maxn];
int n;
inline int lowbit(int x){return x&(-x);}
void add(int pos,LL val){
    for(int i=pos;i<=n;i+=lowbit(i)){
        bit[i] +=val;
    }
}
LL sum(int pos){
    LL res=0;
    for(int i=pos;i;i-=lowbit(i)) res+=bit[i]; 
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%d",&n)==1){
        memset(bit,0,sizeof(bit));
        LL res=0;
        for(int i=1;i<=n;++i){
            LL val; scanf("%lld",&val);
            add(val,1);
            res+= i-sum(val);
        }         
        if(res%2==n%2) printf("Petr\n");
        else printf("Um_nik\n");
    }
    return 0;
}
