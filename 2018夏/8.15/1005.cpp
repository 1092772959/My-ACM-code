#include<bits/stdc++.h>
using namespace std;
const int maxn = 70010;
typedef long long LL;

char mp[3][3];

void C(int pos)
{
    int i=1,j=1;
    if(pos==2) j++;
    else if(pos==3) i++;
    else if(pos==4) i++,j++;
    char tmp = mp[i][j];
    mp[i][j] = mp[i+1][j];
    mp[i+1][j] = mp[i+1][j+1];
    mp[i+1][j+1] = mp[i][j+1];
    mp[i][j+1] = tmp;
}

void R(int pos)
{
    int i=1,j=1;
    if(pos==2) j++;
    else if(pos==3) i++;
    else if(pos==4) i++,j++;
    char tmp = mp[i][j];
    mp[i][j] = mp[i][j+1];
    mp[i][j+1] = mp[i+1][j+1];
    mp[i+1][j+1] = mp[i+1][j];
    mp[i+1][j] = tmp;
}


int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    scanf("%d",&T);
    while(T--){
        int Q;
        scanf("%d",&Q);
        char str[100];
        for(int i=1;i<=3;++i){
            scanf("%s",str+1);
            for(int j=1;j<=3;++j){
                mp[i][j] = str[j];
            }
        }
        char op[5];
        while(Q--){
            scanf("%s",op);
            if(op[1]=='C'){
                C(op[0]-'0');
            }   
            else{
                R(op[0]-'0');
            }         
        }
        for(int i=1;i<=3;++i){
            for(int j=1;j<=3;++j){
                printf("%c",mp[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
