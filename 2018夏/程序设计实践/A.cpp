#include<bits/stdc++.h>
using namespace std;
typedef long double LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
/*
int getInt(string &s)
{
    istringstream iss(s);
    int num, tot = 0,i=0;
    while(iss >> vis[i].val){
        vis[i++].id=tot++;
    }
    return tot;
}
*/

int main()
{
    int T=1,N;
    char op,tmp;
    string str;
    bool plus,tag;
    while(cin>>str){
        int i=0;
        LL a=0,b=0,c=0;
        if(str[i]=='-'){
            plus=false;
            i++;
        }
        else
            plus=true;

        for(;i<str.size();++i){
            a*=10;
            if(plus)    a+=str[i]-'0';
            else    a-=str[i]-'0';       
        }
   ///////////////////////////////////////////   
        cin>>op;

        cin>>str;
        i=0;  
        if(str[i]=='-'){
            plus = false;
            i++;
        }
        else
            plus = true;

        for(;i<str.size();++i){
            b*=10;
            if(plus)    b+=str[i]-'0';
            else    b-=str[i]-'0';
        }
        i+=2;
  ///////////////////////////////////////////////////////////     
        cin>>tmp;
        cin>>str;
        i=0;
        if(str[i]=='-'){
            plus = false;
            i++;
        }
        else
            plus = true;

        for(;i<str.size();++i){
            c*=10;
            if(plus)    c+=str[i]-'0';
            else    c-=str[i]-'0';
        }
        //cout<<a<<" "<<b<<" "<<c<<endl;
        tag=true;
        if(op=='+' && a+b!=c){
            tag=false;
        }
        else if(op=='-' && a-b!=c){
            tag=false;
        }
        else if(op=='*' && a*b!=c){
            tag=false;
        }
        else if(op=='/' && a/b!=c){
            tag=false;
        }
        else
            tag=true;

        printf("Case %d: ",T++);
        if(tag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}