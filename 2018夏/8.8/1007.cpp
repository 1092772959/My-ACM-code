#include<bits/stdc++.h>
const int MAX = 2e5+5;
#define EPS (1.0 / (points - 1))
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;

LL fpow(LL a,LL n)
{
    LL res=1;
    while(n){
        if(n&1) res= res* a %mod;
        a = a*a%mod;
        n>>=1;
    }
    return res;
}

struct Edge{
    int x,y,len;
    double temp;
    bool operator <(const Edge &a)const {return len < a.len;}
    void Read() { scanf("%d%d%d",&x,&y,&len);}
}edge[MAX];

int points,edges;
int father[MAX];
 
int Find(int x){ return father[x] ==x? x:father[x] = Find(father[x]);}

inline int MST(){
    for(int i = 1; i <= points; ++i)    father[i] = i;
    int re = 0;
    for(int i = 1; i <= edges; ++i) {
        int fx = Find(edge[i].x);
        int fy = Find(edge[i].y);
        if(fx != fy) {
            father[fx] = fy;
            re += edge[i].len;
        }
    }
    return re;
}
bool cmp(const Edge &a,const Edge &b){    return a.temp < b.temp;}

int P,Q;
double ans;
LL res;
inline void Calc(int sum){
    double average = (double)sum/(points-1);
    for(int i = 1; i <= points; ++i)    father[i] = i;  
    for(int i = 1; i <= edges; ++i)
        edge[i].temp = (average - edge[i].len) * (average - edge[i].len);
    sort(edge + 1,edge + edges + 1,cmp);
    int re = 0,cnt=0;;
    for(int i = 1; i <= edges; ++i){
        int fx = Find(edge[i].x);
        int fy = Find(edge[i].y);
        if(fx != fy) {
            father[fx] = fy;
            re += edge[i].temp;
            cnt++;
            if(cnt==points-1) break;
        }
    }
    double tmp = re/(points-1);
    if(tmp<ans ){
        ans = tmp;
        P = re;
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
        scanf("%d%d",&points,&edges);
        for(int i = 1; i <= edges; ++i) edge[i].Read();
        sort(edge + 1,edge + edges + 1);
        int range_min = MST();
        reverse(edge + 1,edge + edges + 1);
        int range_max = MST();
        ans = 1e60;
        for(int i = range_min; i <= range_max; ++i)    
            Calc(i);
        res  = P*fpow(points-1,mod-2)%mod;
        printf("%lld\n",res);
    }
    return 0;
}

/*

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn= 1e5+5;
double const MAX = 10000000000000.0;
const int mod = 998244353;
int n, m, tmp[maxn<<1], fa[maxn];
double ans;
struct Edge{
    int u, v,val;
    double w;
}e[maxn<<1];
 
LL fpow(LL a,LL n)
{
    LL res=1;
    while(n){
        if(n&1) res= res* a %mod;
        a = a*a%mod;
        n>>=1;
    }
    return res;
}

bool cmp(Edge a, Edge b){  return a.w < b.w;}
 
void initUF(int n){    for(int i = 1; i <= n; i++) fa[i] = i;}
 
inline int Find(int x){ return x == fa[x] ? x : fa[x] = Find(fa[x]);}
 
void Union(int a, int b)
{
    int r1 = Find(a);
    int r2 = Find(b);
    if(r1 != r2)   fa[r2] = r1;
}

int P;
void Kruskal(int sum)
{
    initUF(n);
    double f_all = 0;
    int all = 0,cnt = 0;
    double ave = sum * 1.0 / (n - 1);
    for(int i = 0; i < m; i++)   e[i].w = (double)(e[i].val - ave) * (e[i].val - ave);
    sort(e, e + m, cmp);
    for(int i = 0; i < m; i++) {
        int u = e[i].u;
        int v = e[i].v;
        if(Find(u) != Find(v)) {
            Union(u, v);
            f_all += e[i].w;
            all += e[i].val;
            cnt ++;
            if(cnt == n - 1)   break;
        }
    }
    if(ans > f_all){
        ans =  f_all;
        P = all;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int ca = 1,T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m);
        int minv = 0, maxv = 0;
        ans = MAX;
        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].val);
            tmp[i] = e[i].val;
        }
        sort(tmp, tmp + m);
        for(int i = 0; i < n - 1; i++)  minv += tmp[i];
        for(int i = m - 1; i > m - n; i--) maxv += tmp[i];
        for(int i = minv; i <= maxv; i++)
            Kruskal(i);
        LL res = P*fpow(n-1,mod-2)%mod;
        printf("%lld\n",res);
    }
}
*/