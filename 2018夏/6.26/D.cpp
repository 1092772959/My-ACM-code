#include<bits/stdc++.h>
#define Fast_in ios_base::sync_with_stdio(false);   cin.tie(0);
using namespace std;
const int maxn =30;
const int INF = 0x3f3f3f3f;
vector<int> vis[maxn];

void init()
{
    for(int i=0;i<maxn;++i){
        vis[i].clear();
    }
}

int main()
{
    Fast_in;
    string str,op;
    char ch;
    int q,t,top,pos;
    while(cin>>str){
        init();
        stack<int> sta;
        for(int i=0;i<str.size();++i){
            vis[str[i]-'a'].push_back(i);
        }

        cin>>q;
        for(int i=0;i<q;++i){
            cin>>op;
            if(op=="push"){
                cin>>ch;
                t = ch-'a';
                if(sta.empty()) top = -1;
                else   top = sta.top();
                int pos = upper_bound(vis[t].begin(),vis[t].end(),top)-vis[t].begin();
                if(pos==vis[t].size()) {
                    printf("NO\n");
                    sta.push(INF);
                }
                else{
                    printf("YES\n");
                    sta.push(vis[t][pos]);
                }
            }
            else{               //pop
                sta.pop();
                if(!sta.empty() &&sta.top()>=str.size())
                    printf("NO\n");
                else
                    printf("YES\n");
            }
        }
    }
    return 0;
}