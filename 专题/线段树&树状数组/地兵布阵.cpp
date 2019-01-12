#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int bit[maxn];
inline int lowbit(int x) {return x&(-x);}
int N;
void add(int pos,int v){
    for(int i =pos;i<=N;i+=lowbit(i)) bit[i]+=v;
}

int query(int pos){
    int ans=0;
    for(int i=pos;i;i-=lowbit(i)) ans+=bit[i];
    return ans;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,k,v;
    int L,R,cas=1;
    char op[10];
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(bit,0,sizeof(bit));
        for(int i=1;i<=N;++i){
            scanf("%d",&v);
            add(i,v);
        }
        printf("Case %d:\n",cas++);
        while(scanf("%s",op)==1){
            if(op[0]=='E') break;
            if(op[0]=='A'){
                scanf("%d%d",&L,&v);
                add(L,v);
            }
            else if(op[0]=='S'){
                scanf("%d%d",&L,&v);
                add(L,-v);
            }
            else{
                scanf("%d%d",&L,&R);
                printf("%d\n",query(R)-query(L-1));
            }
        }
    }
    return 0;
}