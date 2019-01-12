#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
struct Circle{
    LL x,y,r;
}p[maxn];
struct Node{
    LL l,r;  
    bool operator <(const Node & p ) const{
        if(l==p.l) return r>p.r;
        return l<p.l;
    }
};

vector<Node> vz;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;scanf("%d",&T);
    while(T--){
        LL N,M,Q;
        scanf("%lld%lld%lld",&N,&M,&Q);
        LL ans = N*M;
        for(int i =0;i<Q;++i) scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].r);
        for(int i=0;i<N;++i){
            vz.clear();
            for(int j=0;j<Q;++j){
                LL delx = abs(i-p[j].x);
                if(delx>p[j].r) continue;
                LL range = (LL)sqrt(p[j].r*p[j].r-delx*delx);
                LL l = max((LL)0,p[j].y-range); 
                LL r = min(M-1,p[j].y+range);
                vz.push_back((Node){l,r});
            }
            sort(vz.begin(),vz.end());
            int sz = vz.size();
            LL r = -1,tot = 0;
            for(int j=0;j<sz;++j){
                if(vz[j].r<=r) continue;
                if(vz[j].l>r) r = vz[j].l;
                else tot--;
                tot += vz[j].r -r +1;
                r = vz[j].r;
            }
            ans -=tot;
        }
        printf("%lld\n",ans);
    }
    return 0;
}