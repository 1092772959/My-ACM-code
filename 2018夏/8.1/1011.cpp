#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int mod = 1e9+7;


int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
       char p[505];
       scanf("%s",p);
       int len = strlen(p);
       bool judge = true;
       int pre = 1;            //前面是前导0,运算符或数字
       for(int i=0;i<len;++i){
            char &c = p[i];
            if(c=='+' || c=='*'){
                if(pre ==1 ||i==0) judge = false;           //前面是运算符或什么都没有
                pre = 1;
            }
            else if(c =='0'){        
                if(!i) pre=0;
                else if(pre==1) pre=0;
                else if(pre==0) judge = false;              //连续两个0，错
            }
            else if(c=='?'){       
                if(pre==1){
                    c = '1';
                    pre = 2;
                }
                else if(pre==0){
                    c = '*';
                    pre=1;
                }
                else{
                    c ='1';
                    pre=2;
                }
            }
            else{                   //非0数
                if(pre==0 && i) judge=false;            //前导0                             
                pre=2;
            }
           if(!judge) break;  
       }
       if(pre==1) judge =false;                 //最后一个是运算符
       if(!judge) printf("IMPOSSIBLE\n");
       else printf("%s\n",p);
    }
    return 0;
}
