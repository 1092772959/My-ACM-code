#include<bits/stdc++.h>
using namespace std;
const int maxn=40;
int a[maxn];
int n,k;
vector<int> vis[2];

void dfs(int sta,int l,int r)
{
    if(l==r){
        vis[r==n].push_back(sta);   
        return;     
    } 
    dfs((sta+a[l])%k,l+1,r);
    dfs(sta,l+1,r);
}

int main(){

    while(scanf("%d%d",&n,&k)==2){
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        vis[0].push_back(0);
        vis[1].push_back(0);
        dfs(0,0,n/2);
        dfs(0,n/2,n);
        sort(vis[0].begin(),vis[0].end());
        vis[0].erase(unique(vis[0].begin(),vis[0].end()),vis[0].end()); //离散化
        int res=0,x,pos;
        for(int i=0;i<vis[1].size();++i){
            x = k-vis[1][i]-1;
            pos = upper_bound(vis[0].begin(),vis[0].end(),x)-vis[0].begin();
            pos--;
            res =max(res,vis[1][i]+vis[0][pos]);
        }    
        printf("%d\n",res);
    }
    return 0;
}
