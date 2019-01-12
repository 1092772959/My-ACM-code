#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<unordered_map>
#include<unordered_set>
using namespace std;
typedef long long LL;
const int maxn = 1e4+5;
const int INF= 0x3f3f3f3F;
//unordered_map<int,int> fa;
int fa[maxn];
void init(int N)
{
    for(int i=0;i<=N;++i){
        fa[i]=i;
    }
}

inline int Find(int x){ return fa[x]==x? x:fa[x]=Find(fa[x]);}

void Union(int a,int b)
{
    int ra =Find(a),rb =Find(b);
    if(ra!=rb){
        if(ra<rb) fa[rb] = ra;      //向小的合并
        else fa[ra] = rb;
    }
}
string name[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,Q,u,v,tmp,K;
    while(scanf("%d",&N)==1){
        init(N);
        unordered_map<string,vector<int> > mp;
        for(int i=1;i<=N;++i){
            cin>>name[i];
            scanf("%d",&K);
            string e;
            for(int j=1;j<=K;++j){
                cin>>e;
                int len = mp[e].size();
                for(int k=0;k<len;++k){
                    Union(mp[e][k],i);
                }
                mp[e].push_back(i);
            }
        }
        map<int,vector<int> > res;
        for(int i=1;i<=N;++i){
            int f = Find(i);
            res[f].push_back(i);
        }   
        map<int,vector<int> >::iterator it;
        for(it = res.begin();it!=res.end();it++){
            vector<int> tmp = it->second;
            cout<<name[tmp[0]];
            for(int k=1;k<tmp.size();++k){
                cout<<" "<<name[tmp[k]];
            }
            printf("\n"); 
        }
    }
    return 0;
}