#include<bits/stdc++.h>
using namespace std;
int trie[400001][26],len,root,tot,sum[400001];
bool p;
char s[11];
void insert()
{
    len=strlen(s);
    root=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!trie[root][id]) 
            trie[root][id]=++tot;       //新建结点
        sum[trie[root][id]]++;          //前缀和次数加1
        root=trie[root][id];
    }
}

int search()
{
    root=0;
    len=strlen(s);
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!trie[root][id]) return 0;
        root=trie[root][id];
    }
    return sum[root];
}
int main()
{
    while(gets(s)){
        if(!p){
            if(strlen(s)) insert();
            else p=1;
        }
        else printf("%d\n",search());
    }
}