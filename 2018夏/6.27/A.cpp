#include<bits/stdc++.h>
using namespace std;
const int maxn =60;
int N,M;

char G[maxn][maxn];

int main()
{
    while(cin>>N>>M){
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                if(i&1) G[i][j]='#';
                else if((i%4==2 &&j==M) ||(i%4==0&&j==1) ){
                    G[i][j]='#';
                }
                else{
                    G[i][j]='.';
                }
            }
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                printf("%c",G[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
