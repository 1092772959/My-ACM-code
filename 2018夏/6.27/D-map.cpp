//DP +math
//hard
#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
typedef pair<int,int> PII;
typedef long long LL;
map<int,int> mp;
PII vis[maxn];
int N;

int gcd(int a,int b){
    return b==0? a:gcd(b,a%b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int x,c,t,gd;
    while(cin>>N){
        mp.clear();
        for(int i=0;i<N;++i){
            cin>>vis[i].first;
        }
        for(int i=0;i<N;++i){
            cin>>vis[i].second;
        }
        mp[0]=0;                    //
        map<int,int>::iterator it;
        for(int i=0;i<N;++i){
            x = vis[i].first;
            c = vis[i].second;
            for(it = mp.begin();it!=mp.end();++it){
                gd = gcd(x,it->first);
                if(mp[gd] && mp[gd] < c+it->second) 
                    continue;
                mp[gd] = c+it->second;
            }
        }
        if(mp[1])   cout<<mp[1]<<endl;
        else cout<<"-1"<<endl;
    }
    return 0;
}
