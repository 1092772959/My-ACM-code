#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string give="Infinite\n";
void ex_gcd(int a,int b,int &d,int &x,int &y)
{
    if(!b){
        x=1; y=0; d=a;
    }
    else{
        ex_gcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
//ax+py=b等价于ax==b(mod p)
int main()
{
    int a,b,p,x,y,d;
    while(cin>>a>>b>>p){
        ex_gcd(a,p,d,x,y);
        if(b%d!=0)          //无解
            cout<<give;
        else{
            x=x*b/d;
            x = (x%p+p)%p;
            cout<<x<<endl;
        }
    }
    return 0;
}
/*
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
LL Exgcd(LL a,LL b,LL &x,LL &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }
    LL d =  Exgcd(b, a%b, x, y), temp = x;
    x = y;
    y = temp-a/b*y;
    return d;
}
int main()
{
    LL A,B,C,k;
    while(scanf("%lld%lld%lld%lld",&A,&B,&C,&k)==4){
        if(!A&&!B&&!C&&!k) break;
        LL x,y,p;
        k = 1LL<<k;
        p = (B-A+k)%k;
        C %=k;
        LL d = Exgcd(C,k,x,y);
        if(p%d!=0)
            printf("FOREVER\n");
        else{
            x *= p/d;
            x  =(x%(k/d)+(k/d))%(k/d);
            printf("%lld\n",x);
        }
    }
    return 0;
}
*/