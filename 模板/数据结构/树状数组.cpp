#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int bit[maxn];
inline int lowbit(int x) {return x&(-x);}
int N;
void add(int pos,int v){
    for(int i =pos;i<=N;i+=lowbit(i)) bit[i]+=v;
}

int query(int pos){
    int ans=0;
    for(int i=pos;i;i-=lowbit(i)) ans+=bit[i];
    return ans;
}