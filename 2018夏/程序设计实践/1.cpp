#include<bits/stdc++.h>
using namespace std;
const int MOD=26;
map<int,int> mp;
const int maxn =1e5+5;
string res;

int main()
{   
    int n,T=1;
    string str;
    while(getline(cin,str)){
        res.clear();
        int cnt=0,cur=0;
        for(int i=0;i<str.size();++i){
            if(str[i]>='0'&&str[i]<='9'){
                cnt*=10;
                cnt+=str[i]-'0';
            }
            else{
                for(int j=0;j<cnt;++j){
                    res.push_back(str[i]);
                }
                cnt=0;
            }
        }
        reverse(res.begin(),res.end());
        cout<<"Case "<<T++<<": \""<<res<<"\""<<endl;
    }
    return 0;
}