
#include <bits/stdc++.h>
using namespace std;
const int N = 1000+10;
char s[N];
 
void sub(char *s,char *s1)
{
    int num1[N] = {0},num2[N] = {0};
    int lens = strlen(s),lens1 = strlen(s1);
    for(int i = 0;i < lens;i++)
        num1[i] = s[i]-'0';
    for(int i = 0;i < lens1;i++)
        num2[i] = s1[i]-'0';

    for(int i = lens-1,j = lens1-1;i >= 0 && j >= 0;--i,--j)
        num1[i] -= num2[j];
    for(int i = lens-1;i >= 0;i--){
        if(num1[i] < 0){
            num1[i] += 10;
            num1[i-1]--;
        }
    }
    bool flag = true;
    for(int i = 0;i < lens && flag;i++){
        if(num1[i]){
            for(int j = 0;i+j <= lens;j++){
                s[j] = num1[i+j]+'0';
                if(i+j == lens) s[j] = '\0';
            }
            flag = false;
        }
    }
    if(flag)
        strcpy(s,"0");
}
vector<string> res; 
int main()
{
    int T;
    scanf("%d",&T);
    int cas = 1;
    while(T--){
        res.clear();
        scanf("\n%s",s);
        printf("Case #%d:\n",cas++);
        while(true){
            int len = strlen(s);
            char s1[N] = {0};
            s1[len>>1]=s[len>>1];
            for(int i=0;i<len/2;++i){
                s1[i]=s1[len-i-1]=s[i];
            }
            s1[len] = '\0';
            int t = strcmp(s1,s);
            if(t == 0){      
                res.push_back(s1);
                break;
            }
            else if(t < 0){  
                sub(s,s1);
                res.push_back(s1);
            }
            else{            
                char s2[2] = "1";
                for(int i = 0;i < (len+1)/2;i++)
                    s1[i] = s[i];
                s1[(len+1)/2] = '\0';
                sub(s1,s2);                 
                for(int i=0;i<len/2;++i)
                    s1[len-1-i]=s1[i];
                res.push_back(s1);
                sub(s,s1);
            }
        }
        printf("%d\n",res.size());
        for(int i = 0;i < res.size();i++)
            cout<<res[i]<<endl;
    }
    return 0;
}
