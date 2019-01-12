#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+5;
int Next[maxn];
char str[maxn];
int result[maxn];

void GetFailure(int len){
    Next[0]=-1;                             // 初始值为-1
    int j=0,k = -1;
    while (j < len){
        if(k == -1 || str[k] == str[j]){
            ++j;++k;
            Next[j]=k;
        }
        else
            k = Next[k];
    }
}

void solve()
{
    int len = strlen(str),tot=0;
    GetFailure(len);
    int t= Next[len-1];

    while(t!=-1){
        if(str[t]==str[len-1]){
            result[tot++]=t+1;
        }
        t = Next[t];
    }
    for(int i=tot-1;i>=0;--i)    printf("%d ",result[i]);
    printf("%d\n",len);
}

int main()
{
    while(~scanf("%s",str)){
        solve();
    }
    return 0;
}