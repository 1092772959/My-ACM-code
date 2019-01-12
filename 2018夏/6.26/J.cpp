#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
string str[1005];
struct Item{
    LL val;
    char ab;
    int num;
    bool operator < (const Item & p) const{ return val>p.val;}
}vis[30];

bool cmp(const Item & p1,const Item &p2) {
    return p1.ab<p2.ab;
}


LL fpow(LL b,LL n)
{
    LL res=1;
    while(n){
        if(n&1) res*=b;
        b*=b;
        n>>=1;
    }
    return res;
}

int main()
{
    
    int c;
    while(cin>>n){
        memset(vis,0,sizeof(vis));
        for(int i=0;i<10;++i)   vis[i].ab =(char)('a'+i);
        for(int i=0;i<n;++i){
            cin>>str[i];
            for(int j=0;j<str[i].size();++j){
                c =str[i][j]-'a'; 
                vis[c].val += fpow(10,str[i].size()-j-1);  
            }
        }
        sort(vis,vis+10);        //按贡献从大到小
        bool update = true;
        int start =0;
        while(update && start <10){
            update = false;
            for(int i=0;i<n;++i){
                if(vis[start].ab==str[i][0]){
                    start++;
                    update = true;
                    break;
                }
            }
        }
        vis[start].num = 0;
        int cnt =1;
        for(int i=0;i<start;++i){
            vis[i].num = cnt++;
        }
        //abcdefghij
        for(int i=start+1;i<10;++i){
            vis[i].num = cnt++;
        }

        sort(vis,vis+10,cmp);
        LL res=0;
        for(int i=0;i<n;++i){
            for(int j=0;j<str[i].size();++j){
                c = str[i][j]-'a';
                res+= vis[c].num*fpow(10,str[i].size()-j-1);
            }
        }
        cout<<res<<endl;
    }
    return 0; 
}
