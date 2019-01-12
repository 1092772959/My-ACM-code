#include <iostream>
#include <string.h>
#include <cmath>
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <vector>
typedef unsigned long long ull;
typedef long long ll;
const int MOD=1e9+7;
const int maxn=2e5+10;
using namespace std;
int *Rank,r[maxn],sa[maxn],height[maxn],wa[maxn],wb[maxn],wm[maxn];
bool cmp(int *r,int a,int b,int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void SA(int *r,int *sa,int n,int m)
{
    int *x=wa,*y=wb,*t;
    for(int i=0;i<m;++i)wm[i]=0;
    for(int i=0;i<n;++i)wm[x[i]=r[i]]++;
    for(int i=1;i<m;++i)wm[i]+=wm[i-1];
    for(int i=n-1;i>=0;--i)sa[--wm[x[i]]]=i;
    for(int i=0,j=1,p=0;p<n;j=j*2,m=p)
    {
        for(p=0,i=n-j;i<n;++i)y[p++]=i;
        for(i=0;i<n;++i)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<m;++i)wm[i]=0;
        for(i=0;i<n;++i)wm[x[y[i]]]++;
        for(i=1;i<m;++i)wm[i]+=wm[i-1];
        for(i=n-1;i>=0;--i)sa[--wm[x[y[i]]]]=y[i];
        for(t=x,x=y,y=t,i=p=1,x[sa[0]]=0;i<n;++i) {
            x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
        }
    }
    Rank=x;
}
void Height(int *r,int *sa,int n)
{
    for(int i=0,j=0,k=0;i<n;height[Rank[i++]]=k)
    for(k?--k:0,j=sa[Rank[i]-1];r[i+k] == r[j+k];++k);
}

int main()
{
    char s1[maxn],s2[maxn],s3[2*maxn];
    int i,j;
    while(~scanf("%s",s1))
    {
        int n1=strlen(s1);
        int flag=n1;
        int n=n1;
        scanf("%s",s2);
        int n2=strlen(s2);
        for(i=0;i<n1;i++)
            r[i]=s1[i];
        r[n1]='#';  //将待排序的字符串放到r[]中，从r[0]到r[n+1],并且r让r[n+1]=0;
        int k=0;
        for(i=0;i<n2;i++)
            r[n+1+i]=s2[i];
        n+=n2;
        r[n+1]=0;
        SA(r,sa,n+2,256);
        Height(r,sa,n+1);
        //sort(rank,rank+n1+n2);
        //i=1;
        int ans=0;
        for(i=1;i<=n;i++)
        {
            int mi = min(sa[i],sa[i-1]);//名次相邻，且一个在左，一个在右
            int mx = max(sa[i],sa[i-1]);
            if(mi < flag && mx > flag) ans = max(ans,height[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}


/*
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 5e4+10;

int sa[MAXN], Rank[MAXN], height[MAXN];

int temp_arr1[MAXN], temp_arr2[MAXN], cc[MAXN];
void getSA(vector<int>& s, int m=128)
{
    s.push_back(0);

    int *x = temp_arr1, *y = temp_arr2;
    int n = s.size();

    for(int i = 0; i < m; i++) cc[i] = 0;
    for(int i = 0; i < n; i++) cc[x[i] = s[i]]++;
    for(int i = 1; i < m; i++) cc[i] += cc[i - 1];
    for(int i = n-1; i >= 0; i--) sa[--cc[x[i]]] = i;

    for(int j = 1, p = 1; j < n && p < n && !(p=0); j <<=1, m = p)
    {
        for(int i = n-j; i < n; i++) y[p++] = i;

        for(int i = 0; i < n; i++)
            if(sa[i] >= j) y[p++] = sa[i] - j;

        for(int i = 0; i < m; i++) cc[i] = 0;
        for(int i = 0; i < n; i++) cc[x[y[i]]]++;
        for(int i = 1; i < m; i++) cc[i] += cc[i - 1];
        for(int i = n-1; i >= 0; i--) sa[--cc[x[y[i]]]] = y[i];

        swap(x, y); p = 1, x[sa[0]] = 0;
        for(int i = 1; i < n; i++)
        {
            x[sa[i]] = y[sa[i-1]] == y[sa[i]] &&
                    y[sa[i-1]+j] == y[sa[i]+j] ? p-1: p++;
        }
    }
    s.pop_back();
}

void getHeight(const vector<int>& s)
{
    int n = s.size();
    for(int i = 0; i <= n; i++ ) Rank[sa[i]] = i;
    for(int i = 0, k = 0; i < n; i++)
    {
        k? k-- :0;
        int j = sa[Rank[i]-1];
        while( i+k < n && j +k < n &&
            s[i+k] == s[j+k]) k ++;
        height[Rank[i]] = k;
    }
}

int main()
{
    int T;  cin >> T;
    while(T--)
    {
        string str;  cin >> str;
        vector<int> s(str.begin(), str.end());

        getSA(s);
        getHeight(s);
        
        int ans = 0;
        for(int i = 1; i <= s.size(); i++)
            ans += s.size()- sa[i] - height[i];
        cout << ans << endl;
    }
    return 0;
}

*/