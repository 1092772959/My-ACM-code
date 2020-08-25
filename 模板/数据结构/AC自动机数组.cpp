#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;


char s[151][MAXN], T[MAXN];
int n, cnt;

struct node{
    int next[26], fail, flag;
    void clear() {
        memset(next, 0, sizeof(next));
        fail = flag = 0;
    }
}trie[MAXN]; 

void insert(char *s, int num){
    int u = 1, len = strlen(s);
    for(int i=0;i < len; ++i){
        int v = s[i] - 'a';
        if(!trie[u].next[v]){
            trie[u].next[v] = ++cnt;
        }
    }
    trie[u].flag = ++cnt; 
}

void getFail(){
	for(int i=0;i<26;i++) trie[0].next[i]=1;			//初始化0的所有儿子都是1
	queue<int> q;
    q.push(1);
    trie[1].fail=0;				//将根压入队列
	while(!q.empty()){
		int u=q.front();
        q.pop();
		for(int i=0;i<26;i++){				//遍历所有儿子
			int v=trie[u].next[i];			//处理u的i儿子的fail，这样就可以不用记父亲了
			int Fail=trie[u].fail;			//就是fafail，trie[Fail].next[i]就是和v值相同的点
			if(!v){                         //不存在该节点，第二种情况
                trie[u].next[i]=trie[Fail].next[i];
                continue;
            }
			trie[v].fail=trie[Fail].next[i];	//第三种情况，直接指就可以了
			q.push(v);						//存在实节点才压入队列
		}
	}
}

int query(char* s){
    int u = 1, ans = 0, len = strlen(s);
    for (int i=0;i<len; ++i){
        int v = s[i] - 'a';
        int k = trie[u].next[v];
        while(k > 1 && trie[k].flag != -1){
            ans += trie[k].flag;
            trie[k].flag = -1;
            k = trie[k].fail;
        }
        u = trie[u].next[v];
    }
    return ans;
}
