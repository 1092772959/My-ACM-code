#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int sg(ll x)
{
    if(x%4==0)  return x-1;
    else if(x%4==3)  return x+1;
    else return x;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T,n;
    cin>>T;
    while(T--){
        cin>>n;
        ll e,ans=0;
        for(int i=0;i<n;++i){    
            cin>>e;        
            ans^=sg(e);
        }
        if(ans) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}