#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e2+5;
LL deq[maxn];
int st,ed,N;
LL a[maxn];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&N);  
        st = ed = 0;
        LL res = 0;
        int cnt = 0;
        for(int i=1;i<=N;++i){
            scanf("%lld",&a[i]);
            if(st==ed || deq[a[ed]]<=a[i]){
                deq[ed++] = i;
            }
            else{
                while(st<ed-1){
                    res+= -a[deq[st]] + a[deq[ed-1]];
                    cnt+= 2;
                    st++,ed--;
                }
                if(st==ed-1){
                    if(a[deq[st]]>=a[i]) st++;
                }
                deq[ed++] = i;
            }
        }
        while(st<ed-1){
            res += -a[deq[st]] + a[deq[ed-1]];
            cnt += 2;
            st++,ed--;
        }
        printf("%lld %d\n",res,cnt);
    }
	return 0;
}

