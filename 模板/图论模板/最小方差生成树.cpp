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