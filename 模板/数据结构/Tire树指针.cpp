#include<bits/stdc++.h>
using namespace std;
char s[11];
int n,m;
bool p;
struct node
{
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
     while(*word)
    {
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
    while(*word)
    {
        int id=*word-'a';
        r=r->next[id];
        if(r==NULL) return 0;
        word++;
    }
    return r->count;
}
int main()
{
    root=build();
    while(gets(s)){
        if(!p) {
            if(strlen(s)) insert();
            else p=true;
        }
        else printf("%d\n",search());
    }

}