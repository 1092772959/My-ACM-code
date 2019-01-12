#include<bits/stdc++.h>
using namespace std;
typedef long long LL;


#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,s,t,u,v,T;
    LL tmp,b;
    char str[2500];
    while(scanf("%d",&N)==1){
        scanf("%s",str);
        int len = strlen(str);
        for(int i=0;i<len;++i)   //1
            printf("***");
        printf("\n");
        for(int i=0;i<len;++i){  //2
            char c = str[i];
            if(c=='A' || c=='B'||c=='D') printf("*.*");
            else  printf("*..");
        }
        printf("\n");
        for(int i=0;i<len;++i){
            char c  =str[i];
            if(c=='A'||c=='B'||c=='E') printf("***");
            else if(c=='C') printf("*..");
            else printf("*.*");
        }
        printf("\n");
        for(int i=0;i<len;++i){
            char c = str[i];
            if(c=='A' || c=='B'||c=='D') printf("*.*");
            else  printf("*..");
        }
        printf("\n");
        for(int i=0;i<len;++i){
            char c = str[i];
            if(c=='A') printf("*.*");
            else  printf("***");
        }
        printf("\n");
    }  
    return 0;
}
