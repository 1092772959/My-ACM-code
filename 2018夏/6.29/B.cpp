#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
const int INF = 0x3f3f3f3f;
int N;
int pos[maxn];              //pos[i]记录的是值为i的数最后一次出现的位置

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while(cin>>N){
        memset(pos,0,sizeof(pos));
        int res=2,a;
        for(int i=1;i<=N;++i){
            cin>>a;
            if(pos[a-1]>pos[a+1])   res = max(res,i-max(pos[a+1],pos[a-2]));
            else res= max(res,i-max(pos[a-1],pos[a+2]));
            pos[a]=i;
        }
        cout<<res<<endl;
    }
    return 0;
}