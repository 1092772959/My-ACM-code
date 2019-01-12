#include<bits/stdc++.h>
using namespace std;

int cnt[30];

int main()
{
    string str;
    int T=1;
    while(getline(cin,str)){
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<str.size();++i){
            if(str[i]>='A'&&str[i]<='Z'){
                str[i]+=32;
                cnt[str[i]-'a']++;
            }
            else if(str[i]>='a'&&str[i]<='z'){
                cnt[str[i]-'a']++;
            }
            else;
        }
        printf("Case %d: ",T++);
        for(int i=0;i<25;++i){
            printf("%d ",cnt[i]);
        }
        printf("%d\n",cnt[25]);
    }
    return 0;
}