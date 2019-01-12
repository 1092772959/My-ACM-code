#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define N 10000
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--){
      char str[N];
      int len;int i;int mod;
      long long ans=0;
      scanf("%s",str);
      //getchar();
      //scanf("%d",&mod);
      mod=13;
      len=strlen(str);
      for(i=0;i<len;i++)
        ans=(ans*10+str[i]-'0')%mod;    //  ???
      ans=(int)ans;
      if(ans!=0)
        printf("No\n");
      else
        printf("Yes\n");
    }
    return 0;
}