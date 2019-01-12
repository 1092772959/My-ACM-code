#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int n;
string num;

int main()
{
    while(~scanf("%d",&n)){
        cin>>num;
        int tag,e=num[0]-'0';
        int pre1,pre2;
        bool flag = true;
        if(n==1 && num[0]=='0') flag = false;
        
        if(n>=2){
            if(num[0]=='0'&&num[1]=='0') flag = false;
            if(num[n-1]=='0' && num[n-2]=='0') flag = false;
            if(num[0]=='1' && num[1]=='1') flag =false;
        }
        
        pre2=num[0]-'0',pre1= num[1]-'0';
        for(int i=2;i<n && flag;++i){
            e = num[i]-'0';
            if(!e && !pre1 && !pre2) flag = false;
            if(e && pre1) flag = false;
            pre2 = pre1;
            pre1 = e;
        }

        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}