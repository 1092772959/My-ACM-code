#include<bits/stdc++.h>
using namespace std;
const int MOD=26;


int main()
{
    string str1,str2;
    string res1,res2;
        int T=1;
    while(getline(cin,str1)){
        res1.clear();
        res2.clear();
        getline(cin,str2);
        int cnt=0;
        int i,len=min(str1.size(),str2.size());
        for( i=0;i<len;++i){
            if(str1[i]==str2[i]){
                cnt++;
                continue;
            } 
            else{
                break;
            }
        }
        int st=i;
        for(int i=st;i<str1.size();++i)
            res1.push_back(str1[i]);

        for(int i=st;i<str2.size();++i)
            res2.push_back(str2[i]);
        cout<<"Case "<<T++<<": "<<cnt<<endl;
        cout<<"\""<<res1<<"\""<<endl;
        cout<<"\""<<res2<<"\""<<endl;
    }
    return 0;
}