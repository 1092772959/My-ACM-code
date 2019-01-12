#include<bits/stdc++.h>
using namespace std;
const int maxn =1e6+5;
typedef long long ll;
vector<ll> Next;

void init()
{
    ll t;
    queue<ll> Q;
    Q.push(0);
    while(!Q.empty()){
        t = Q.front();Q.pop();
        if(t>1e11) continue;
        Next.push_back(t);
        Q.push(t*10+4);
        Q.push(t*10+7);
    }
    sort(Next.begin(),Next.end());
}

int bisearch_L(ll val)
{
    int L=0,R=Next.size()-1,mid,res=Next.size()-1;
    while(L<=R){
        mid = (L+R)/2;
        if(Next[mid]<=val){
            res = mid;
            L = mid+1;
        }
        else
            R = mid-1;
    }
    return res;
}

int bisearch_R(ll val)          //
{
    int L=0,R=Next.size()-1,mid,res=0;
    while(L<=R){
        mid = (L+R)/2;
        if(Next[mid]>=val){
            res = mid;
            R = mid-1;
        }
        else{
            L = mid+1;
        }
    }
    return res;
}

ll f(ll L,ll R)
{
    ll res=0;
    int posL = bisearch_R(L);
    int posR = bisearch_R(R);
    int posRL = bisearch_L(R);
    if(Next[posL]>=R){
        return (ll)(R-L+1)*Next[posL];
    }
    res+=(Next[posL]-L+1)*Next[posL];
    res+=(R-Next[posRL])*Next[posR];
    for(int i=posL;i<posRL;++i){
        res+=(Next[i+1]-Next[i])*Next[i+1];
    }
    return res;
}

int main()
{
    ll L,R;
    init();
    while(cin>>L>>R)
        cout<<f(L,R)<<endl;
    return 0;
}