#include<bits/stdc++.h>
using namespace std;
int N;
const int maxn = 105;
vector<int> G[30];
int indeg[30];
vector<char> res;

bool circle()
{
    priority_queue<int, vector<int>, greater<int> > Q;
    int cnt=0;
    for(int i=0;i<26;++i){
        if(!indeg[i]){
            Q.push(i);
            cnt++;
            res.push_back((char)('a'+i));
        }
    }
    int v;
    while(!Q.empty()){
        v = Q.top();Q.pop();
        for(int i=0;i<G[v].size();++i){
            int u = G[v][i];
            indeg[u]--;
            if(!indeg[u]){
                Q.push(u);
                cnt++;
                res.push_back((char)('a'+u));
            }
        }
    }
    if(cnt!=26)return true;
    else return false;
}

void print()
{
    if(circle()){
        printf("Impossible\n");
        return ;
    }
    for(int i=0;i<25;++i){
        printf("%c",res[i]);
    }
    printf("%c\n",res[25]);
}

int main()
{
    string str[maxn];
    int c1,c2;
    while(scanf("%d",&N)==1){
        memset(indeg,0,sizeof(indeg));
        res.clear();
        cin>>str[1];
        bool update;
        for(int i=2;i<=N;++i){
            cin>>str[i];
            update = false;
            for(int j =0;j<str[i].size()&& j<str[i-1].size();++j){
                c1 = str[i-1][j]-'a';
                c2 = str[i][j]-'a';
                if(c1==c2)  continue;
                G[c1].push_back(c2);     
                indeg[c2]++;
                update = true;         
                break; 
            }
            if(!update && str[i-1].size()>str[i].size()){
                G[c1].push_back(c2);
                indeg[c2]++;
            }
        }
        /*
        for(int i=0;i<26;++i)
            printf("%d ",indeg[i]);
        system("pause");
        */
        print();
    }
    return 0;
}