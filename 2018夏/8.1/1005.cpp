#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e2+5;
LL M[maxn][maxn];
int A[maxn];
int L;

LL area(int x,int y){
    LL block = M[L-1][L-1];         //一个块的和
    LL res=block *(x/L)*(y/L);
    res+=M[x%L][y%L];
    res+=(x/L)*M[L-1][y%L];
    res+=(y/L)*M[x%L][L-1];
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,Q,u,v,tmp,K;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i=0;i<N;++i)
            scanf("%d",&A[i]);
        if(N&1) L =N*2;
        else L = (N<<2); 
        int cur = 0;
        for(int i=0;i<L;++i){
            for(int j=0;j<=i;++j){
                M[j][i-j] = A[cur];
                cur  = (cur+1) %N;
            }
        }
        L/=2;
        for(int i=0;i<L;++i){
            for(int j=0;j<L;++j){
                M[i][j] +=M[i][j-1];
                M[i][j] +=M[i-1][j];
                M[i][j] -=M[i-1][j-1];
            }
        }
        scanf("%d",&Q);
        while(Q--){
            int a,b,c,d;
            scanf("%d%d%d%d",&a,&b,&c,&d);
            LL res = area(c,d)+area(a-1,b-1)-area(c,b-1)-area(a-1,d);
            printf("%lld\n",res);
        }
    }
    return 0;
}
