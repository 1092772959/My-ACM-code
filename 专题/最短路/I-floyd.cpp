#include<iostream>
#include<cstring>
#include<stdio.h>
#include<map>
#include<string>
#include<camth>
#include<algorithm>
//#define LOCAL
using namespace std;
const int maxn =1e2+5;
#define eps 1e-10
int N,M;
double G[maxn][maxn];

void init()
{
    memset(G,0,sizeof(G));
    for(int i=0;i<=N;++i){
        G[i][i]=1.0;
    }
}

void show()
{
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string num,num2;
    int u,v,tmp,T=1;
    double e;
    map<string,int> mp;
    while(cin>>N, N){
        init();
        for(int i=1;i<=N;++i){
            cin>>num;
            mp[num] = i;
        }
        cin>>M;
        for(int i=1;i<=M;++i){
            cin>>num>>e>>num2;
            u = mp[num],v = mp[num2];
            G[u][v] = max(G[u][v],e);
        }
        for(int k=1;k<=N;++k){
            for(int i=1;i<=N;++i){
                if(!G[i][k]) continue;
                for(int j=1;j<=N;++j){
                    if(!G[k][j]) continue;
                    if(G[i][j]<G[i][k]*G[k][j]){
                        G[i][j]  =G[i][k]*G[k][j];
                    }
                }
            }
        }
        //show();
        bool flag = false;
        for(int i=1;i<=N;++i){
            if(G[i][i]-1.0>eps){
                flag = true;
                break;
            }
        }
        cout<< "Case "<<T++<<": ";
        if(flag) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}