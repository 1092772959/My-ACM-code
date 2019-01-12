    #include<bits/stdc++.h>
    using namespace std;
    const int INF = 0x3f3f3f3f;
    const int maxn = 305;

    struct Spfa{
        int N;
        int G[maxn][maxn];
        int d[maxn];
        bool vis[maxn];

        void init(int N){ this->N=N;}

        void spfa(int s){
            memset(vis,0,sizeof(vis));
            queue<int> Q;
            for(int i=1;i<=N;++i){
                d[i]=G[s][i];
                if(i!=s){
                    Q.push(i);
                    vis[i]= true;
                }
            }
            d[s]=INF;
            while(!Q.empty()){
                int x =Q.front();Q.pop();
                vis[x] = false;
                for(int i =1;i<=N;++i){
                    if(x==i) continue;
                    if(d[i]>d[x]+G[x][i]){
                        d[i]=d[x]+G[x][i];
                        if(!vis[i]){
                            Q.push(i);
                            vis[i]=true;
                        }
                    }
                }    
            }
        }
    }G;


    #define LOCAL
    int main()
    {
        #ifdef LOCAL
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
        #endif
        int N,M,s,t,u,v,T,tmp;
        while(~scanf("%d",&N)){
            if(!N) break;
            G.init(N);
            for(int i =1;i<=N;++i){
                for(int j=1;j<=N;++j){
                    scanf("%d",&G.G[i][j]);
                }
            }
            G.spfa(1);
            int res=G.d[N];
            int cir1=G.d[1];
            G.spfa(N);
            int cir2 = G.d[N];
            res=min(res,cir1+cir2);
            printf("%d\n",res);
        }
        return 0;
    }

