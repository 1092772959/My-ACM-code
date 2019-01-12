#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn =2e3+5;
int fa[maxn],num[maxn];
int pos[maxn];                  //错误发生的编号
void init(int N){
    for(int i=0;i<=N;++i){
        fa[i]=i;
        num[i]=0;
    }
}
//模3系
inline int Find(int x){
    if(fa[x]==x) return x;
    int f = fa[x];
    fa[x] = Find(fa[x]);
    num[x] = (num[x]+num[f])%3;
    return fa[x];
}
bool Union(int a,int b,int op)
{
    int roota = Find(a),rootb =Find(b);
    if(roota==rootb){
        if((num[a]+op)%3!=num[b]) return false;
        else return true;
    }
    fa[rootb] = roota;
    num[rootb] = (-num[b]+num[a]+op+3)%3; 
    return true; 
}
struct Query{
    int a,b,op;
}p[maxn];

int main(){
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,T,Q,u,v,tmp,cas=1,a,b;
    char op;
    while(scanf("%d%d",&N,&M) == 2 ){
        memset(pos,-1,sizeof(pos));
        for(int i=1;i<=M;++i){
            scanf("%d%c%d",&p[i].a,&op,&p[i].b);
            if(op=='=') p[i].op=0;
            if(op=='<') p[i].op=1;
            if(op=='>') p[i].op=2;
        }
        for(int i=0;i<N;++i){               //尝试枚举每个人不是judge的可能
            init(N);
            for(int j=1;j<=M;++j){
                if(i==p[j].a || i==p[j].b) continue;        //跳过包含i的条件
                if(!Union(p[j].a,p[j].b,p[j].op)) {
                    pos[i]=j;
                    break;                          //找到错误的发生即可推断出judge在i之外的人中
                }
            }
        }
        int cnt=0,ans1=0,ans2=0;
        for(int i=0;i<N;++i){
            if(pos[i]==-1){                     //如果排除这个人不会产生问题，那么他就可以是judge
                cnt++;
                ans1 = i;
            }
            ans2 = max(ans2,pos[i]);            //推断n-1个人不是judge之后，也就知道了谁是judge
        }
        if(cnt>1) printf("Can not determine\n");
        else if(cnt==0) printf("Impossible\n");
        else printf("Player %d can be determined to be the judge after %d lines\n",ans1,ans2);
    }
    return 0;
}
