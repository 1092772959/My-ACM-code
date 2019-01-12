#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int ans[maxn];          //ans[i]:i的约数个数
void pre()
{
    for(int i=1;i<=1e6;++i){
        for(int j=0;j<=1e6;j+=i){
            ans[j]++;
        }
    }
}