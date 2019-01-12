#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
typedef long long LL;
LL tab1[maxn];
LL tab2[maxn];
void pre()
{
    for(int a=3;a<=40000;++a){
        if(a&1){
            LL n =(a-1)>>1;
            LL nf = n*n;
            tab1[a] = 2*nf+2*n;
            tab2[a] = 2*nf+2*n+1;
        }
        else{
            LL n = a>>1;
            LL nf = n*n;
            tab1[a] =  nf-1;
            tab2[a] =  nf+1;
        }
    }    
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T; scanf("%d",&T);
	while (T--){
        LL n,a; scanf("%lld %lld",&n,&a);
        if(n>2 ||n==0){
            printf("-1 -1\n"); 
        }
        else{
            if(n==1){
                printf("1 %d\n",a+1);
            }
            else if(n==2){
                printf("%lld %lld\n",tab1[a],tab2[a]);
            }
        }
	}
	return 0;
}

