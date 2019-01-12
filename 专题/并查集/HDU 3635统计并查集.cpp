#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn =2e4+5;
int fa[maxn],cnt[maxn],val[maxn];

void init(int N){
    for(int i=0;i<=N;++i){
        fa[i]=i;
        cnt[i]=0,val[i]=1;
    }
}

inline int Find(int x){
    if(fa[x]==x) return x;
    int f = fa[x];
    fa[x] = Find(fa[x]);
    cnt[x] +=cnt[f];
    return fa[x];
}

void Union(int a,int b){
    int ra = Find(a),rb = Find(b);
    if(ra != rb){
        fa[ra]= rb;
        val[rb]+=val[ra];
        cnt[ra]++;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,T,Q,u,v,tmp,cas=1,a,b;
    char op[3];
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&Q);
        init(N);
        printf("Case %d:\n",cas++);
        while(Q--){
            scanf("%s",op);
            if(op[0]=='T'){
                scanf("%d%d",&u,&v);
                Union(u,v);
            }
            else{
                scanf("%d",&a);
                int ra= Find(a);
                printf("%d %d %d\n",ra,val[ra],cnt[a]);
            }
        }
    }
    return 0;
}
