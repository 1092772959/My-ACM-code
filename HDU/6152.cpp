#include<bits/stdc++.h>
using namespace std;
const int maxn =3e3+5;
bool G[maxn][maxn];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    while(T--){
        int N; scanf("%d",&N);
        bool flag = true;
        if(N>=6) flag = false;
        int tmp ;
        for(int i=1;i<N;++i){
            for(int j=i+1;j<=N;++j){
                scanf("%d",&tmp);
                G[i][j] = G[j][i] = tmp;
            }
        }
        for(int i=1;i<=N;++i){
            int know = 0;
            for(int j=1;j<=N;++j){
                if(i==j) continue;
                if(G[i][j]) know++; 
            }
            if(know>=3 ||N-know-1>=3) flag = false;
        }
        if(flag) printf("Great Team!\n");
        else printf("Bad Team!\n");
    }
    return 0;
}