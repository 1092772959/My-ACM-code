#include<bits/stdc++.h>
#define LL long long
#define FOR(i,f_start,f_end) for(int i=f_start;i<=f_end;++i)
#define mem(a,x) memset(a,x,sizeof(a))
#define lson l,m,x<<1
#define rson m+1,r,x<<1|1
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double PI = acos(-1.0);
const double eps = 1e-8;
const int maxn = 1e4 + 5;
const int maxs = 20;
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n , m;
int d[maxn][maxs];
int height[maxn], rnk[maxn];
void build_sa(int m)
{
	int i, *x = t, *y = t2;
	for ( i = 0; i < m; i++)		c[i] = 0;
	for ( i = 0; i < n; i++)		c[x[i] = s[i]]++;
	for ( i = 1; i < m; i++)	    c[i] += c[i - 1];
	for (i = n - 1; i >= 0; i--)	sa[--c[x[i]]] = i;
	for (int k = 1; k <= n; k <<= 1){
		int p = 0;
		for (i = n - k; i < n; i++)
			y[p++] = i;
		for (i = 0; i < n; i++){
			if (sa[i] >= k)
				y[p++] = sa[i] - k;
		}
		for (i = 0; i < m; i++)	c[i] = 0;
		for (i = 0; i < n; i++)
			c[x[y[i]]]++;
		for (i = 0; i < m; i++)
			c[i] += c[i - 1];
		for (i = n - 1; i >= 0; i--)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1;	x[sa[0]] = 0;
		for (i = 1; i < n; i++){
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		}
		if (p >= n)	break;
		m = p;
	}
}
int cmp_suffix(char *pattern, int p)
{
	return strncmp(pattern, s + sa[p], m);
}
int find(char *P)
{
	m = strlen(P);
	if (cmp_suffix(P, 0) < 0)	return -1;
	if (cmp_suffix(P, n - 1)>0)	return -1;
	int left = 0, right = n - 1 , mid;
	while (left <= right){
		mid = left + (right - left) / 2;
		int res = cmp_suffix(P, mid);
		if (!res)	return mid;
		if (res < 0)		right = mid - 1;
		else     left = mid + 1;
	}
	return -1;
}

void getHeight()
{
	int i, j, k = 0;
	for (i = 0; i < n; i++)	rnk[sa[i]] = i;
	for (i = 0; i < n; i++){
		if (k)	k--;
		 j = sa[rnk[i] - 1];
		while (s[i + k] == s[j + k])	k++;
		height[rnk[i]] = k;
	}
}

void RMQ_init()
{
    for(int i = 0 ; i<n; i++)       d[i][0] = sa[i];
    for(int j = 1 ; (1<<j) - 1 <=n ; j++){
        for(int i = 0 ; i + (1<<j) - 1 < n ; i++){
            d[i][j] = min(d[i][j-1] , d[i + (1<< (j - 1))][ j -1 ]);
        }
    }
}

int RMQ(int L , int R){
    int k = 0;
    while((1<<(k + 1)) <= R - L + 1)    k++;
    return min(d[L][k] , d[R - (1 << k) + 1][k]);
}

int main()
{
	char query[1005];
	scanf("%s", s);
	n = strlen(s);
	build_sa('z' + 1 );
	while (scanf("%s", query) == 1){
		int ans = find(query);
		printf("%d\n", ans);
	}
	return 0;
}
