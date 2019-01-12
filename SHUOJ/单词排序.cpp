#include<bits/stdc++.h>
using namespace std;
int n ;
struct People{
    int id;
    string name;
    int rank;
    bool operator < (const People & p )const {return name<p.name;}
}p[300005];

bool cmp(const People & p1,const People &p2){
    return p1.id<p2.id;
}

int main()
{
    char x[40];
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while(cin>>n){
        for(int i=1;i<=n;++i){
            cin>>p[i].name;
            p[i].id=i;
        }   
        sort(p,p+n);
        for(int i =1;i<=n;++i){
            p[i].rank=i;
        }
        sort(p,p+n,cmp);
        for(int i=1;i<=n;++i){
            cout<<p[i].rank<<endl;
        }
    }
    return 0;
}