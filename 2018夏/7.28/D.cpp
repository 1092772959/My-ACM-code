#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;

int main(){
    int T,M,num,t,x;
    int L,R;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int cas=1;
    int N;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        double res= (N-1)*1.0;
        printf("Case #%d: %.7f\n",cas++,res);
    }
    return 0;
}