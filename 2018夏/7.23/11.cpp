#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

char op[100];

void update(int &h,int &m)
{
    if(m>=60){
        m-=60;
        h++;
    }
    if(h>=24){
        h-=24;
    }
    if(m<0){
        m+=60;
        h--;
    }
    if(h<0){
        h+=24;
    }
}

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    int h,m;
    scanf("%d",&T);
    while(T--){
        memset(op,0,sizeof(op));
        scanf("%d%d%s",&h,&m,op);
        int tag=1;
        if(op[3]=='-') tag=-1;
        int x=0,y=0,len = strlen(op);
        bool dot = false;
        for(int i=4;i<len;++i){
            if(op[i]=='.'){
                dot = true;
                continue;
            }
            int c= op[i]-'0';
            if(!dot){
                x*=10;
                x+=c;
            }
            else{
                y+=c;
            }
        }
        int tot =(x*10+y);
        tot = (tag*tot-80);
        h+=(tot/10);
        m+=6*(tot%10);
        update(h,m);
        char res1[10],res2[10];
        res1[0]=h/10+'0',res1[1]=h%10+'0',res1[2]='\0';
        res2[0]=m/10+'0',res2[1]=m%10+'0',res2[2]='\0';
        printf("%s:%s\n",res1,res2);
    }
    return 0;
}
