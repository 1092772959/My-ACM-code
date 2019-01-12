#include<bits/stdc++.h>
using namespace std;

char s[100];         //用于插入
int len1,len2;


struct node{
    int count;              //记录以从根结点到当前字母为前缀的单词个数
    node * next[26];
}*root;                     //根
node * build()
{
    node * k=new(node);
    k->count=0;
    memset(k->next,0,sizeof(k->next));
    return k;
}
void insert()
{
    node * r=root;
    char * word=s;
     while(*word){
        int id=*word-'a';
        if(r->next[id]==NULL) r->next[id]=build();
        r=r->next[id];
        r->count++;
        word++;
    }
}

int search()
{
    node * r=root;
    char * word=s;
    int length=0,id;
    
    return length;
}

int main()
{
    root=build();
    int N,M;
    while(scanf("%d%d",&N,&M)==2){
        for(int i=1;i<=N;++i){
            scanf("\n%s",s);
            insert();
        }
        
        for(int i=1;i<=M;++i){
            len1=len2=0;
            scanf("\n%s",s);
            int lenq=strlen(s),res;
            int length = search();

            cout<<len1<<" "<<len2<<endl;
            
            printf("%d\n",res);
        }
    }    
    return 0;
}