#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn =5e4+5;
const int mod = 300;
int fa[maxn],dist[maxn];

void init(int N){
    for(int i=0;i<=N;++i){
        fa[i]=i;
        dist[i]=0;
    }
}

inline int Find(int x){
    if(fa[x]==x) return x;
    int f = fa[x];
    fa[x] = Find(fa[x]);
    dist[x] =(dist[x]+dist[f])%mod;    
    return fa[x];
}

bool Union(int a,int b,int d){
    int ra = Find(a),rb = Find(b);
    if(ra==rb){
        if((dist[a]+d)%mod !=dist[b]) return false;
        else return true;
    }
    fa[rb] = ra;
    dist[rb] = (-dist[b]+dist[a]+d+mod)%mod;
    return true;
}

int main(){
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,T,Q,u,v,tmp,cas=1,a,b;
    char op[3];
    while(scanf("%d%d",&N,&M)==2){
        int res=0;
        init(N);
        while(M--){
            scanf("%d%d%d",&u,&v,&tmp);
            if(!Union(u,v,tmp)) res++; 
        }
        printf("%d\n",res);
    }
    return 0;
}
