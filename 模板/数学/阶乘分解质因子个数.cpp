#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

void factoN(int n,int *c)      //分解阶乘
{
    for(int i=n;i>1;--i){
        int tmp = i;
        for(int j=2;j*j<=tmp;++j){
            while(tmp%j==0){
                c[j]++;
                tmp/=j;
            }
        }
        if(tmp!=1) c[tmp]++;
    }
}
