#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
typedef long long LL;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int p;
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&p);
        for(int i=0;i<p;++i){
            for(int j=0;j<p;++j){
                printf("%d%c",(i+j)%p,j==p-1?'\n':' ');
            }
        }
        for(int i=0;i<p;++i){
            for(int j=0;j<p;++j){
                printf("%d%c",(i*j%p),j==p-1?'\n':' ');
            }       
        }
    }
	return 0;
}

