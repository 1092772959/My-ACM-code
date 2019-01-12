#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL fpow(LL b,LL n){
    LL res=1;
    while(n){
        if(n&1) res=res*b;
        b=b*b;
        n>>=1;
    }
    return res;
}

int main()
{
    LL N,B,a;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>N>>B){
        LL res1=0,res2=0;
        for(int i=0;i<N;++i){
            cin>>a;
            res1+=a*fpow(B,N-i-1);
        }
        cin>>N>>B;
        for(int i=0;i<N;++i){   
            cin>>a;
            res2+=a*fpow(B,N-i-1);
        }
        if(res1==res2)    cout<<"="<<endl;
        else if(res1<res2)    cout<<"<"<<endl;
        else cout<<">"<<endl;
    }
    return 0;
}