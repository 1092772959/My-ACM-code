#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200007;
int N, m, tot;
int h[200005];
int st[MAXN][32-__builtin_clz(MAXN)];
int dp[200005];
int sel[200005], pre[200005], c[200005];

void init_st() {
  int l = 31 - __builtin_clz(N);
  for(int i=0;i<N;++i) st[i][0] = h[i];
  for(int j=0;j<l;++j) 
    for (int i=0;i<1+N-(1<<j);++i)
        st[i][j+1] = max(st[i][j], st[i+(1<<j)][j]);
}

int rmq(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  return max(st[l][k], st[r-(1<<k)+1][k]);
}

int getbignext(int pos, int val) {
    int l = pos + 1, r = N, mid; 
    while (r > l) {
        mid = (l + r) / 2;
        if (rmq(pos+1, mid) <= val) l = mid + 1;
        else r = mid;
    }
    return l;
}
void initdp() {
    int cnt = 1;
    dp[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        int pos = getbignext(i, h[i]);
        dp[i] = dp[pos] + 1;
    }
    sel[0] = 1; pre[0] = -1; c[0] = 1;
    int last = 0, lasth = h[0];
    for (int i = 1; i < N; i++) {
        pre[i] = last;
        if (h[i] > lasth){
            sel[i] = 1;
            last = i;
            lasth = h[i];
            cnt++;
        } 
        else sel[i] = 0;
        c[i] = cnt;
    }
  tot = cnt;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;scanf("%d",&T);
    while(T--){
        int Q;
        scanf("%d%d",&N,&Q);
        for(int i=0;i<N;++i) scanf("%d",&h[i]);
        init_st();
        initdp();
        int p,q;
        while(Q--){
            scanf("%d%d",&p,&q);
            p--;
            int res=0;
            if(sel[p]){         //这个位置保持递增
                if(p==0){
                    res = dp[getbignext(p,q)]+1;
                }
                else{
                    if(q>h[pre[p]]){
                        res += c[p];
                        res += dp[getbignext(p,q)];
                    }
                    else{
                        res += c[pre[p]];
                        res += dp[getbignext(p,h[pre[p]])];
                    }
                }
            }
            else{
                if(q<=h[pre[p]]){
                    res= tot;
                }
                else{
                    res += c[pre[p]]+1;
                    res += dp[getbignext(p,q)];
                }
            }
            printf("%d\n",res);
        }
    }
    return 0;
}
