#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double lb;
LL limit =1e9;
int main(){
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    LL a,b;
    char p1[100],p2[100];
    while(scanf("%lld.%s",&a,p1)==2){
        scanf("%lld.%s",&b,p2);
        for(int i=0;i<9;++i){
            a*=10;
            a+=(p1[i]-'0');
        }
        for(int i=0;i<9;++i){
            b*=10;
            b+=(p2[i]-'0');
        }
        LL t =a%b;
        LL c1=t/limit ,c2 =t%limit;
        char res[100];
        int cnt=0;
        if(!c1) res[cnt++]='0';
        else{
            stack<int> S;
            while(c1){
                S.push(c1%10);
                c1/=10;
            }
            while(!S.empty()){
                int x= S.top();S.pop();
                res[cnt++]= x+'0';
            }
        }
        if(c2){
            res[cnt++]='.';
            stack<int> S;
            for(int i=1;i<=9;++i){
                S.push(c2%10);
                c2/=10;
            }   
            while(!S.empty()){
                int x= S.top();S.pop();
                res[cnt++]= x+'0';
            }
        }
        res[cnt]='\0';
        printf("%s\n",res);
        memset(p1,0,sizeof(p1));
        memset(p2,0,sizeof(p2));
    }
    return 0;
}
