#include<bits/stdc++.h>
using namespace std;
typedef int LL;
LL gcd(LL a,LL b){
    if(b==0) return a;
    return gcd(b,a%b);
}
LL vz[105];

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int T,N;
    string str;
    scanf("%d",&T);
    getline(cin,str);
    while(T--){
        N =0;
        getline(cin,str);
        istringstream is(str);
        while(is>>vz[N]) N++;
        int res=1;
        for(int i=0;i<N;++i){
            for(int j=i+1;j<N;++j){
                res = max(res,gcd(vz[i],vz[j]));
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
