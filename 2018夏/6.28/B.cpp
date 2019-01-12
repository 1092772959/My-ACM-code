#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
char res[maxn];
int main()
{
    string num;
    while(cin>>num){
        memset(res,0,sizeof(res));
        int i,dot=1,tot=0,ex=0,first=0;
        bool zero = true;

        if(num[0]=='0') dot--;
        for(i=0;num[i]!='e';++i){
            if(num[i]=='.') continue;
            if(zero && num[i]!='0'){
                zero = false;
            }
            if(!zero){
                res[tot++]=num[i];             
            }
        }
        
        if(zero){
            cout<<"0"<<endl;
            continue;
        }

        for(i+=1;i<num.size();++i){
            ex*=10;
            ex+=(int)(num[i]-'0');
        }
        dot+=ex;
    

        if(dot>=1){
            if(dot>tot){
                for(int i=tot;i<dot;++i)
                    res[i]='0';
            }
            else if(dot<tot){
                for(int i=tot;i>dot;--i){
                    res[i]=res[i-1];
                }
                if(res[tot]!='0')   res[dot]='.';
                else res[dot]='\0';
            }
            else;
        }
        else{
            int step= 1-dot;
            for(int i=tot-1;i>=0;--i){
                res[i+step+1]=res[i];
            }
            res[0]='0';
            res[1]='.';
            for(int i=2;i<=step;++i){
                res[i]='0';
            }
        }
        cout<<res<<endl;
    }
    return 0;
}