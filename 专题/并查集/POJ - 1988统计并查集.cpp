#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
const int INF= 0x3f3f3f3f;
int fa[maxn],cnt[maxn],s[maxn];
void init(int N){
    for(int i=0;i<=N;++i)
        fa[i]=i,cnt[i]=0,s[i]=1;
}
//cnt[i]记录i之下的箱子数，s[i]记录包括i在内i之上的箱子数
int Find(int x)
{
    if(fa[x]==x) return x;
    int f= fa[x];
    fa[x] = Find(fa[x]);
    cnt[x] +=cnt[f];
    return fa[x];
}

void Union(int a,int b)
{
    int rta =Find(a),rtb = Find(b);
    if(rta!=rtb){
        fa[rta] = rtb;
        cnt[rta]=s[rtb];
        s[rtb]+=s[rta];
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K,cas=1,x,y;
    char op[5];
    while(scanf("%d",&N)==1){
        init(N);
        while(N--){
            scanf("%s",op);
            if(op[0]=='C'){
                scanf("%d",&x);
                Find(x);                        //查找前要路径压缩一下
                printf("%d\n",cnt[x]);
            }   
            else{
                scanf("%d%d",&x,&y);
                Union(x,y);
            }
        }
    }
    return 0;
}
