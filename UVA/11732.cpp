#include<bits/stdc++.h>
using namespace std;
#define maxnode 62
int trie[1005][maxnode],len,root,tot,sum[400001];
bool p;
char s[1005];

void init()
{
    memset(trie,0,sizeof(trie));
    memset(sum,0,sizeof(sum));
}

int getidx(char c){
    if(c>='0'&&c<='9')  return c-'0';
    else if(c>='a'&&c<='z') return 10+c-'a';
    else return 36+c-'A';
}

void insert()
{
    len=strlen(s);
    root=0;
    for(int i=0;i<len;i++){
        int id=getidx(s[i]);
        if(!trie[root][id]) 
            trie[root][id]=++tot;       //新建结点
        sum[trie[root][id]]++;          //前缀和次数加1
        root=trie[root][id];
    }
}

int dfs(int root)
{
    int ans=0;
    if(!root) ans+=sum[1];
    else ans+=sum[root];
    for(int i=0;i<maxnode;++i){
        if(trie[root][i]){
            ans+=dfs(trie[root][i]);
        }
    }
    return ans;
}

int main()
{
    int N,T=1;
    while(~scanf("%d",&N),N){
        for(int i=1;i<=N;++i){
            scanf("\n%s",s);
            insert();
        }
        printf("%d\n",dfs(1));
    }
    return 0;
}
