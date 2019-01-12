#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 3e5+5; 

int main() 
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int N;
    double M;
    while(scanf("%d%lf",&N,&M)==2){
        long double tot=0;
        vector<pair<int,int> > v;
        for(int i=1,a,b;i<=N;++i){
            scanf("%d%d",&a,&b);
            v.push_back(make_pair(a,1));
            v.push_back(make_pair(b+1,-1));
            tot+= (b-a+1);
        }
        sort(v.begin(),v.end());
        int ans=0 ,cnt=0;
        for(auto &t :v){
            cnt += t.second;
            ans = max(cnt,ans);
        }
        tot/=1.0*M;
        printf("%d\n%.13Lf\n",ans,tot);
    }
    return 0;
}