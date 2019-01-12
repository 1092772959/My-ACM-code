#include<bits/stdc++.h>
using namespace std;
const int maxn =505;
bool used[maxn];
string name[maxn];
struct Node{
    int id;
    double val;
    bool operator < (const Node &p) const{
        return val<p.val;
    }
}a[maxn],b[maxn];

int main()
{
    int N;
    while(~scanf("%d",&N)){
        vector<string> res;
        string first;
        double tot=0;
        memset(used,0,sizeof(used));
        for(int i=1;i<=N;++i){
            cin>>name[i]>>a[i].val>>b[i].val;
            //scanf("%s%f%f",&name[i],&a[i].val,&b[i].val);
            a[i].id = b[i].id = i;
        }
        sort(a+1,a+N+1);
        sort(b+1,b+N+1);
        
        for(int i=1;i<=N;++i){
            cout<<name[a[i].id]<<"\t"<<name[b[i].id]<<endl;
        }
        int cnt=0;
        for(int i=1;i<=N && cnt <3;++i){
            bool flag=true;
            for(int j=i-1;flag && j>=1;--j){
                if(a[j].id==b[i].id) flag = false;
            }
            if(!flag) continue;
            res.push_back(name[b[i].id]);
            tot+=b[i].val;
            used[b[i].id] = true;
            cnt++;
        }
        for(int i=1;i<=N;++i){
            if(!used[a[i].id]){
                first = name[a[i].id];
                tot+=a[i].val;
                break;
            }
        }
        cout<<tot<<endl;
        cout<<first<<endl;
        for(int i=0;i<3;++i){
            cout<<res[i]<<endl;
        }
    }
    return 0;
}