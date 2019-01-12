#include<bits/stdc++.h>
using namespace std;
string s;
int n,k;
struct node{
    int num,dao;
    bool operator < (const node&a) const{
        if(num==a.num) return dao > a.dao;
        else return num < a.num;
    }
}aa;
priority_queue<node> q;

int main()
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    while(~scanf("%d%d",&n,&k)){
        cin>>s;
        int num=0;
        if(k==0) {
            for(int i=0;i<=n-1;i++)
                if(s[i]=='0') break;
                else num++;
            printf("%d\n",num);
            continue;
        }

        int sta=0,end_=n-1;
        for(sta=0 ;sta<=n-1;sta++) if(s[sta]=='0')break;
        if(sta!=0) q.push(node{sta,1});
        for(end_=n-1;end_>=sta&&end_>=0;end_--,num++) if(s[end_]=='0') break;
        if(num!=0) q.push(node{num,1});
        num=0;
        for(int i=sta;i<=end_;i++){
            if(s[i]=='0'&&num!=0){
                    q.push(node{num,2});
                    num=0;
                }
            else if(s[i]=='0') num=0;
            else num++;
        }
        int ans=0;
        int flag=0;
        while(!q.empty()){
            node v=q.top();
            q.pop();
            int dd=v.dao,nn=v.num;
            if(k==0&&dd==1){
                k-=dd;
                ans+=nn;
            }
            else if(k==0) continue;
            else {
                k-=dd;
                ans+=nn;
            }
            if(k<0) break;
        }
        printf("%d\n",ans);
        while(!q.empty()) q.pop();
    }
    return 0;
}

