#include<bits/stdc++.h>
using namespace std;
const int maxn =505;
const int INF =0x3f3f3f3f;
int G[maxn][maxn];
int path[maxn][maxn];
string str[maxn];
void init(int N)
{
    for(int i=1;i<=N;++i){
        G[i][i]=INF;
        path[i][i]=-1;
        for(int j=i+1;j<=N;++j){
            G[i][j]=G[j][i]=INF;
            path[i][j]=path[j][i]=-1;
        }
    }
}

void Floyd(int N)
{
    for(int k=1;k<=N;++k){
        for(int i=1;i<=N;++i){
            if(G[i][k]==INF) continue;
            for(int j=1;j<=N;++j){
                if(G[k][j]==INF) continue;
                if(G[i][k]+G[k][j]<G[i][j]){
                    G[i][j]=G[i][k]+G[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

void show(int N)
{
    for(int i =1;i<=N;++i){
        for(int j=1;j<=N;++j){
            cout<<path[i][j]<< " ";
        }
        cout<<endl;
    }
}


int main()
{
    int N,k,u,v;
    while(scanf("%d",&N)==1){
        init(N);
        map<string,int> mp;
        string tmp,op;
        for(int i =1;i<=N;++i){
            cin>>tmp;
            str[i] = tmp;
            mp[tmp]=i;
        }
        for(int i=1;i<=N;++i){
            cin>>tmp>>k;
            u = mp[tmp];
            for(int j=0;j<k;++j){
                while(true){
                    cin>>tmp;
                    if(tmp=="import") continue;
                    int len = tmp.size();
                    if(tmp[len-1]!=','){
                        v = mp[tmp];
                        G[u][v]=1;
                        path[u][v]=u;
                        break;
                    }
                    else{           //后面跟逗号
                        tmp=tmp.substr(0,len-1);
                        v = mp[tmp];
                        G[u][v]=1;
                        path[u][v] = u;
                    }
                }
            }
        }
        Floyd(N);
        //show(N);
        int st=-1,res=INF,ed;
        for(int i=1;i<=N;++i){
            if(G[i][i]<res){
                st= i;
                res=G[i][i];
            } 
        }
        ed = st;
        if(st==-1){
            printf("SHIP IT\n");
            continue;
        }
        stack<int> S;
        int cnt=0;
        while(cnt<res){
            S.push(path[st][ed]);
            ed = path[st][ed];
            cnt++;
        }
        while(!S.empty()){
            int x =S.top();S.pop();
            cout<<str[x];
            if(!S.empty()) cout<<" ";
            else cout<<endl;
        }
        
    }
    return 0;
}