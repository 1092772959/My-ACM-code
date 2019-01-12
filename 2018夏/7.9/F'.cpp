#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+10;
typedef long long LL;
int N;
map<LL, LL> cnt;
set<LL> st;
int main()
{
    int T; cin >> T;
    while(T--){
        cnt.clear(), st.clear();
        scanf("%d", &N );
        LL Max = 0,x;
        for( int i = 0; i < N ; i++ ){
            scanf("%lld", &x);
            st.insert(x), cnt[x]++;
            Max = max(Max, x);
        }

        if( st.find(1) != st.end() ){
            printf("%d\n", N);
            continue;
        }
        
        for( LL x : st){
            for( LL i = 2 ;x* i <= Max ; i++){
                LL tmp=x*i;
                if( st.find(tmp) != st.end() ){
                    st.erase(tmp);
                    cnt[x] += cnt[tmp], cnt[tmp] = 0;
                }
            }
        }

        LL  ans = 0;
        for( LL x : st)
            ans += cnt[x]* x;
        printf("%lld\n", ans);
    }
    return 0;
}