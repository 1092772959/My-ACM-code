#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int N,M;
int a[maxn];
int ans[maxn];
struct Query{
    int L,R,id;
    bool operator < (const Query &q) const {return R<q.R;}
}Q[maxn];

int bit[maxn];
inline int lowbit(int x) {return x&(-x);}

void add(int i,int val){
    for(;i<=N;i+=lowbit(i)) bit[i]+=val;
}

int sum(int i){
    int res=0;
    for(;i>0;i-=lowbit(i)) res+=bit[i];
    return res;
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    int cas=1;
    while(scanf("%d%d",&N,&M)==2){
        vector<int> pos[maxn];
        memset(bit,0,sizeof(bit));
        for(int i=1;i<=N;++i){
            scanf("%d",&a[i]);
        }
        
        for(int i=1;i<=M;++i){
            scanf("%d%d",&Q[i].L,&Q[i].R);
            Q[i].id = i;
        }
        sort(Q+1,Q+M+1);

        int la=1;
        for(int i=1;i<=N;++i){
            if(a[i]<=N){                        //如果a[i]>N 那么不可能对结果有贡献
                pos[a[i]].push_back(i);         //记录出现的位置
                int sz = pos[a[i]].size();
                if(sz>=a[i]){                     
                    add(pos[a[i]][sz-a[i]],1);                  //对从右往左数的第a[i]次出现的位置，加1
                    //若a[i]出现的次数大于a[i]，从右往左数出现的第a[i]+1次的位置已经被加1，不能作出贡献的前缀被多加了2，所以减去2
                    if(sz>a[i]) add(pos[a[i]][sz-a[i]-1],-2);
                    //但是若a[i]出现的次数大于a[i]+1,那么之前的-2操作就需要“补偿回来”
                    if(sz>a[i]+1) add(pos[a[i]][sz-a[i]-2],1);
                }
            }
            while(la<=M && Q[la].R==i){
                ans[Q[la].id] = sum(Q[la].R) - sum(Q[la].L-1);
                la++;
            }
            if(la>M) break;
        }
        for(int i=1;i<=M;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}