#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
typedef long long LL;
int vis[maxn];
LL sum;
int getInt(string &s)
{
    istringstream iss(s);
    int num, tot = 0,i=0;
    while(iss >> vis[i]){
        tot++;
        i++;
    }
    return tot;
}

int main()
{
    int T=1;
    string s;
    while(getline(cin,s)){
        int tot = getInt(s);
        
    }
    return 0;
}