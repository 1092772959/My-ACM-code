#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int n,m,q;
map<string,int> dict;
int pre[maxn];
int dist[maxn];

int Find(int x)
{
    if( x != pre[x]){
        int j = pre[x];
        pre[x] = Find(j);
        dist[x] ^=dist[j];
    }
    return pre[x];
}

bool Union(int &a,int &b,int &op)
{
    op--;
    int roota = Find(a);
    int rootb = Find(b);
    if(roota != rootb){
        pre[rootb]= roota;
        dist[rootb] = (op+dist[a]-dist[b]+2)%2;       //向量三角
    }
    else{
        if((dist[a]-dist[b]+2)%2!=op)
            return false;
    }
    return true;
}

int main()
{
    string name,p1,p2;
    int x,y,op,fx,fy;
    while(~scanf("%d%d%d",&n,&m,&q)){
        for(int i=1;i<=n;++i){
            cin>>name;
            dict[name]=i;
            pre[i]=i;
            dist[i]=0;
        }
        for(int i=1;i<=m;++i){
            cin>>op>>p1>>p2;
            x= dict[p1];
            y= dict[p2];
            if(Union(x,y,op)) printf("YES\n");
            else printf("NO\n");
        }   
        for(int i=1;i<=q;++i){
            cin>>p1>>p2;
            x = dict[p1];   fx=Find(x);   
            y = dict[p2];   fy=Find(y);
            if(fx!=fy)
                printf("3\n");
            else{
                if((dist[x]+dist[y])%2==1)  printf("2\n");
                else printf("1\n");
            }
        }     
    }
    return 0;
}