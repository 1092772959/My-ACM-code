#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

int main()
{
    int T=1;
    int a,b;
    //string str;
    char str[1005];
    char eq='=';
    int cas;
    cin>>cas;
    getchar();
    while(cas--){
        gets(str);
        int res=0;
        int len = strlen(str);
        for(int i=0;i<len;++i){
            if(str[i]>='a'&&str[i]<='z')
                res+=str[i]-'a'+1;
            else if(str[i]>='A' && str[i]<='Z')
                res+=str[i]-'A'+1;
            else;
        }  
        cout<<"Case "<<T++<<": "<<str<<" = "<<res<<endl;
    }
    return 0;
}