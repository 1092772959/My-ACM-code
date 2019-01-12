#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
struct Node{
    int L,R;
    bool f;     //表示L>=R 和L<R的两种状态
    bool operator < (const Node &rhs)const {
        if(f){
            if(!rhs.f) return true;         //L>=R的状态要排在L<R之前
            else return R<rhs.R;            //状态相同则比较关键字R
        }
        else{
            if(rhs.f) return false;         //同理
            else return L>rhs.L;
        }

    }
}p[maxn];

#define LOCAL
int main(){
        #ifdef LOCAL
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
        #endif
        int T,N,M,u,v,tmp,K,cas=1;
        scanf("%d",&T);
        while(T--){
            scanf("%d",&N);
            int res=0;
            for(int i=0;i<N;++i){
                char op[maxn];
                scanf("%s",op);
                int L=0,R=0,len=strlen(op);
                for(int j=0;j<len;++j){
                    if(op[j]=='(') L++;
                    else{
                        if(L){L--;res+=2;}
                        else R++;
                    }
                }
                p[i].L = L,p[i].R=R,p[i].f= (L>=R?true:false);
            }
            sort(p,p+N);
            int preL=0,tmp;
            for(int i=0;i<N;++i){
                tmp = min(preL,p[i].R);
                res+=2*tmp;
                preL-=tmp;
                preL+=p[i].L;
            }
            printf("%d\n",res);
        }
        return 0;
    }
