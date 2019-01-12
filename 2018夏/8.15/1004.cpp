#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;
typedef long long LL;
char res[maxn][maxn];

int h,w;

void debug()
{
    for(int i=1;i<=h;++i){
        for(int j=1;j<=w;++j){
            printf("%c",res[i][j]);
        }
        printf("\n");
    }
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
        scanf("%d%d",&h,&w);
        if(h&1 && w&1){
            for(int i=1;i<=h;++i){
                for(int j=1;j<=w;++j){
                    res[i][j] = '(';
                }
            }
            debug();
            continue;
        }

        if(h==w){                            //行偶列偶
            if(w<=6){
                for(int i=1;i<=h;++i){
                    if(i&1){
                        res[i][1] ='(';
                        for(int j=2;j<w;++j){
                            if(j&1) res[i][j] =')';
                            else res[i][j] = '('; 
                        }
                        res[i][w] = ')';
                    }
                    else{
                        for(int j=1;j<=w;++j){
                            if(j&1) res[i][j] = '(';
                            else res[i][j] =')';
                        }
                    }
                }
            }
            else{
                for(int j =1;j<=w;++j) res[1][j] = '(',res[h][j] = ')';
                for(int i=2;i<h;++i){
                    if(i&1){
                        res[i][1] ='(';
                        for(int j=2;j<w;++j){
                            if(j&1) res[i][j] =')';
                            else res[i][j] = '('; 
                        }
                        res[i][w] = ')';
                    }
                    else{
                        for(int j=1;j<=w;++j){
                            if(j&1) res[i][j] = '(';
                            else res[i][j] =')';
                        }
                    }
                }
            }
        }

        else if(h>w){           //行大
            if(w&1){                        //行偶列奇
                for(int i=1;i<=h;++i){
                    for(int j=1;j<=w;++j){
                        if(i&1) res[i][j] = '(';
                        else res[i][j] = ')';
                    }
                }
            }
            else if(h&1){
                for(int i=1;i<=h;++i){
                    for(int j=1;j<=w;++j){
                        if(j&1) res[i][j] = '(';
                        else res[i][j] = ')';
                    }
                }
            }
            else{                           //行偶列偶
                if(w<=6){
                    for(int i=1;i<=h;++i){
                        if(i&1){
                            res[i][1] ='(';
                            for(int j=2;j<w;++j){
                                if(j&1) res[i][j] =')';
                                else res[i][j] = '('; 
                            }
                            res[i][w] = ')';
                        }
                        else{
                            for(int j=1;j<=w;++j){
                                if(j&1) res[i][j] = '(';
                                else res[i][j] =')';
                            }
                        }
                    }
                }
                else{           //w>=8
                    for(int j =1;j<=w;++j) res[1][j] = '(',res[h][j] = ')';
                    for(int i=2;i<h;++i){
                        if(i&1){
                            res[i][1] ='(';
                            for(int j=2;j<w;++j){
                                if(j&1) res[i][j] =')';
                                else res[i][j] = '('; 
                            }
                            res[i][w] = ')';
                        }
                        else{
                            for(int j=1;j<=w;++j){
                                if(j&1) res[i][j] = '(';
                                else res[i][j] =')';
                            }
                        }
                    }
                }
            }
        }
        else {                  //列大
                if(h&1){                        //行奇列偶
                    for(int i=1;i<=h;++i){
                        for(int j=1;j<=w;++j){
                            if(j&1) res[i][j] = '(';
                            else res[i][j] = ')';
                        }
                    }
                }
                else if(w&1){
                    for(int i=1;i<=h;++i){
                        for(int j=1;j<=w;++j){
                            if(i&1) res[i][j] = '(';
                            else res[i][j] = ')';
                        }
                    }
                }
                else{                           //行偶列偶
                    if(h<=6){
                        for(int i=1;i<=w;++i){
                            if(i&1){
                                res[1][i] = '(';
                                for(int j=2;j<h;++j){
                                    if(j&1) res[j][i] =')';
                                    else res[j][i] = '('; 
                                }
                                res[h][i] =')';
                            }
                            else{
                                for(int j=1;j<=h;++j){
                                    if(j&1) res[j][i] = '(';
                                    else res[j][i] =')';
                                }
                            }
                        }
                    }
                    else{                   //h>=8
                        for(int i =1;i<=h;++i) res[i][1] = '(',res[i][w] = ')';
                        for(int i= 2;i<w;++i){
                            if(i&1){
                                res[1][i] ='(';
                                for(int j=2;j<h;++j){
                                    if(j&1) res[j][i] =')';
                                    else res[j][i] = '('; 
                                }
                                res[h][i] = ')';
                            }
                            else{
                                for(int j=1;j<=h;++j){
                                    if(j&1) res[j][i] = '(';
                                    else res[j][i] =')';
                                }
                            }
                        }
                    }   
                }
        }
        debug();
    }
    return 0;
}
