#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
vector<int> p[maxn];
bool is[maxn];

void pre()
{
    for(int i=2;i<maxn;i+=2) {
        p[i].clear();
        p[i].push_back(2);
    }
    for(int i=3;i<maxn;i+=2){
        if(is[i]) continue;
        for(int j=i;j<maxn;j+=i){
            is[j] = true;
            p[j].push_back(i);
        }
    }
}