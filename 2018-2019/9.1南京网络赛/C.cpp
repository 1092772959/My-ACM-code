#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 14;
map<int,int> vz[205];

LL ans[205];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    int T,cas=1; scanf("%d",&T);
    while(T--){
        int N,M; scanf("%d %d",&N, &M);
        queue<int> Q;
        for(int i=1;i<=M;++i){
            int tmp;
            scanf("%d",&tmp);
            if(tmp<=2) tmp+=13; 
            Q.push(tmp);
        }
        for(int i=1;i<=N;++i){
            int cnt = 0;
            while(!Q.empty() && cnt<5){
                cnt++;
                int x = Q.front(); Q.pop();
                vz[i][x]++;
            }
        }
        int win;
        int last=-1,cur=0,pp=-1;
        bool epy = false;
        if(Q.empty()){
            epy = true;
        }
        while(true){
            map<int,int> ::iterator it;
            bool ed = false;
            for(int i=1;i<=N;++i){ 
                if(i==pp){                  //轮了一圈没人出牌，摸牌
                    last = -1;
                    for(int j=0;j<N && !epy;++j){
                        int now = i+j;
                        if(now>N) now-=N;
                        int x = Q.front(); Q.pop();
                        vz[now][x]++;
                        if(Q.empty()) epy = true;
                    }
                }
                if(last == 15) continue;
                bool chu = false;
                for(it =vz[i].begin();it!=vz[i].end();++it){
                    if(it->second==0) continue;
                    int tmp=  it->first; 
                    if(last==-1 || tmp==last+1 || tmp==15){
                        cur = tmp;
                        pp = i;
                        vz[i][tmp]--;
                        chu = true;
                        break;
                    }
                }
                if(!chu) continue;              //没有出牌

                last = cur;
                bool zero = true;
                for(it = vz[i].begin();it!=vz[i].end();++it){
                    if(!it->second) continue;
                    else{
                        zero = false;
                        break;
                    }
                }
                if(zero){
                    ed = true;
                    win = i;
                    break;
                }
            }
            if(ed){         //有人出完了
                break;
            }
        }
        
        printf("Case #%d:\n",cas++);
        for(int i=1;i<=N;++i){
            ans[i] = 0;
            if(i==win){
                printf("Winner\n");
            }   
            else{
                map<int,int> :: iterator it;
                for(it = vz[i].begin();it!=vz[i].end();++it){
                    int tmp = it->first;
                    if(tmp>13) tmp-=13;
                    ans[i] += (LL)tmp*(it->second);
                }
                printf("%lld\n",ans[i]);
            }
            vz[i].clear();
        }
    }
    return 0;
}
