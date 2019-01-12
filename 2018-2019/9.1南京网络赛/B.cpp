#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+9;
const int mod=1e9+7;
#define inf 0x3f3f3f3f
int n,m;
ll s[maxn][102],num[maxn][102];
ll sta[maxn],tt;
ll up[maxn],down[maxn];
void singleupStack(int i,int j)
{
    while(tt && num[i][j] < num[sta[tt]][j]) down[i]+=down[sta[tt]],--tt;
}
void singledownStack(int i,int j)
{
    while(tt && num[i][j] < num[sta[tt]][j]) down[i]+=down[sta[tt]],--tt;
}
int main()
{
     #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    cin>>T;
    int k;
    int Case=0;
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                s[i][j]=1;
            }
        }
        for(int i=0,x,y;i<k;i++)
        {
            scanf("%d%d",&x,&y);
            s[x][y]=0;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(s[i][j]==1)
                {
                    num[i][j]=num[i][j-1]+1;
                }
                else
                {
                    num[i][j]=0;
                }
            }
        }
        ll ans=0;
        for(int j=1;j<=m;j++)
        {
            tt=0;
            for(int i=1;i<=n;i++)
            {
                if(num[i][j]!=0)
                {
                    up[i]=1;
                    while(tt && num[i][j] <= num[sta[tt]][j]) up[i]+=up[sta[tt]],--tt;
                    sta[++tt]=i;
                }
                else
                {
                    tt=0,up[i]=0;
                }
            }
            tt=0;
            for(int i=n;i>=1;i--)
            {
                if(num[i][j]!=0)
                {
                    down[i]=1;
                    while(tt && num[i][j] < num[sta[tt]][j]) down[i]+=down[sta[tt]],--tt;
                    sta[++tt]=i;
                }
                else 
                {
                    tt=0,down[i]=0;
                }
                ans += up[i]*down[i]*num[i][j];
            }
        }
        printf("Case #%d: ",++Case);
        printf("%lld\n",ans);
    }
    return 0;
}