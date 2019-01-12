#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn =1e4+5;
const static int base =31;
int dp[maxn][15];           //do记录大小,pos记录下标
int pos[maxn][15];
ULL w[50];               //每位的权值
char word[40];
bool tag[40][40];       //统计回文子串

void init()
{
    w[0]=1;
    for(int i=1;i<=50;++i)  w[i]=w[i-1]*base;
}

ULL Hash(char *str)                 //哈希
{
    ULL val=0;
    int size = strlen(str);
    for(int i=0;i<size;++i){
        val+=(str[i]-'a'+1)*w[i];
    }
    return val;
}

int palime(char *str){            //n^2暴力枚举回文子串的个数
    int ans=0;
    int len = strlen(str);
    memset(tag,0,sizeof(tag));
    for(int i=len-1;i>=0;--i){
        tag[i][i]=true;
        ans++;
        for(int j=i+1;j<len;++j){
            if(str[i]==str[j]){
                if(i+1==j || tag[i+1][j-1]){
                    tag[i][j]=true;
                    ans++;
                }
            }
            else 
                tag[i][j]=false;
        }
    }
    return ans;
}

void ST(int N)
{
    for(int j=1;(1<<j)<=N;++j){
        for(int i=1;i+(1<<j)<=N+1;++i){
            if(dp[i][j-1]<dp[i+(1<<j-1)][j-1]){
                dp[i][j]=dp[i+(1<<(j-1))][j-1];
                pos[i][j]=pos[i+(1<<(j-1))][j-1];
            }
            else{
                dp[i][j]=dp[i][j-1];
                pos[i][j]=pos[i][j-1];
            }
        }
    }
}

int RMQ(int L,int R)
{
    int k=0;
    while((1<<(k+1))<=R-L+1) k++;
    if(dp[L][k]>=dp[R-(1<<k)+1][k])  return pos[L][k];
    else return pos[R-(1<<k)+1][k];
}

map<ULL,int> mp;            //根据字符串哈希值取下标

int main()
{
    init();
    int T,N,Q;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&Q);
        for(int i=1;i<=N;++i){
            scanf("%s",word);
            mp[Hash(word)] = i;
            dp[i][0] =palime(word);
            pos[i][0]=i;
        }
        ST(N);
        char a[40],b[40];
        int x,y;
        for(int i=0;i<Q;++i){
            scanf("%s",a);
            scanf("%s",b);
            x = mp[Hash(a)];
            y = mp[Hash(b)];
            if(x>y) swap(x,y);
            printf("%d\n",RMQ(x,y));
        }
    }
    return 0;
}

