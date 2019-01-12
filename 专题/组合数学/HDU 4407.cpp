#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+5;
typedef long long LL;
map<int,int> vz;

LL gcd(LL a,LL b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

LL sum1(LL a1,LL an)         //等差数列求和
{
    LL n  = an-a1+1;
    LL res = (a1 + an) * n / 2;
    return res;    
}

LL sum2(LL l,LL r,LL val)     //等比数列求和
{
    int n = ( r / val ) - ( ( l - 1 ) / val ) ;
    int a1 = ( l % val == 0 )? l : ( val - l % val ) + l ;
    int an = r - r % val ;
    LL res = (LL)( a1 + an ) * (LL)n / 2 ; 
    return res;
}

LL cal(int l,int r,int p)
{
    vector<int> fac;
    int tmp = p;
    for(int i=2;i*i<=tmp;++i){
        if(tmp%i==0){
            fac.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp>1) fac.push_back(tmp);
    int cnt = fac.size();
    int up = 1<<cnt;
    LL res=0;
    for(int i=1;i<up;++i){                          //容斥统计与p不互素的数的和
        int bits = 0 ;
        LL ji = 1;
        for(int j=0;j<cnt;++j){
            if(i&(1<<j)){
                bits++;
                ji *= fac[j];
            }
        }
        LL sum= sum2(l,r,ji);
        if(bits &1) res+=sum;
        else res-=sum;         
    }
    res = sum1(l,r)-res;
    for(auto &v :vz){
        if(v.first<l) continue;
        if(v.first>r) break;
        if(gcd(v.first,p)==1) res-=v.first;         //多加了要减去
        if(gcd(v.second,p)==1) res+=v.second;       //修改后的结果与p互质，加上
    }
    return res; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    while(T--){
        int N,M; scanf("%d%d",&N,&M);
        vz.clear();
        int op,x,y,p,c;
        while(M--){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d%d",&x,&y,&p);
                if(x>y) swap(x,y);
                printf("%lld\n",cal(x,y,p));
            }
            else{
                scanf("%d%d",&x,&c);
                vz[x] =c;                   //记录修改
            }
        }
    }
    return 0;
}