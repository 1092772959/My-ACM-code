    #include<bits/stdc++.h>
    using namespace std;
    typedef long long LL;
    const int MAXN = 50010;
    const int MAXM = 1010*1010;
    const int INF = 0x3f3f3f3f;
    int N;
    struct Node{
        int x,y;
    }p[MAXN],it[MAXN];
    int v[MAXN];

    struct Edge{
        int v;
        int next;
    }edge[MAXM];
    
    int nx, ny;
    int cnt;
    int t;
    int dis;

    int first[MAXN];
    int xlink[MAXN], ylink[MAXN]; 
    /*xlink[i]表示左集合顶点所匹配的右集合顶点序号，ylink[i]表示右集合i顶点匹配到的左集合顶点序号。*/
    int dx[MAXN], dy[MAXN]; 
    /*dx[i]表示左集合i顶点的距离编号，dy[i]表示右集合i顶点的距离编号*/
    int vis[MAXN]; //寻找增广路的标记数组 
    void init(){
        cnt = 0;
        memset(first, -1, sizeof(first));
        memset(xlink, -1, sizeof(xlink));
        memset(ylink, -1, sizeof(ylink));
    }
    
    void AddEdge(int u, int v){
        edge[cnt].v = v;
        edge[cnt].next = first[u], first[u] = cnt++;
    }
    
    int bfs()
    {
        queue<int> q;
        dis = INF;
        memset(dx, -1, sizeof(dx));
        memset(dy, -1, sizeof(dy));
        for(int i = 1; i <= nx; i++){
            if(xlink[i] == -1){
                q.push(i);
                dx[i] = 0;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(dx[u] > dis) break;
            for(int e = first[u]; e != -1; e = edge[e].next){
                int v = edge[e].v;
                if(dy[v] == -1){
                    dy[v] = dx[u] + 1;
                    if(ylink[v] == -1) dis = dy[v];
                    else{
                        dx[ylink[v]] = dy[v]+1;
                        q.push(ylink[v]);
                    }
                }
            }
        }
        return dis != INF;
    }
    
    int find(int u)
    {
        for(int e = first[u]; e != -1; e = edge[e].next){
            int v = edge[e].v;
            if(!vis[v] && dy[v] == dx[u]+1){
                vis[v] = 1;
                if(ylink[v] != -1 && dy[v] == dis) continue;
                if(ylink[v] == -1 || find(ylink[v])){
                    xlink[u] = v, ylink[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }
    
    int MaxMatch()
    {
        int ans = 0;
        while(bfs()){
            memset(vis, 0, sizeof(vis));
            for(int i = 1; i <= nx; i++) 
                if(xlink[i] == -1)  
                    ans += find(i);
        }
        return ans;
    }

    const int MAXV = 50005;
    int prime[MAXV];
    bool notprime[MAXV*10];
    void pre()
    {
        int up  = MAXV *10;
        memset(notprime,0,sizeof(notprime));
        notprime[0] = notprime[1] = true;
        memset(prime,0,sizeof(prime));
        for(int i=2;i<up;++i){
            if(!notprime[i]) prime[++prime[0]] = i;
            for(int j=1 ; j<=prime[0] && prime[j] <= up / i ;++j){
                notprime[prime[j]*i] = true;
                if(i%prime[j]==0) break;
            }
        }
    }

    int pos[MAXV*10];
    int num[MAXV];
    int fac[MAXV];
    bool jo[MAXV*10];

    void ADD(int num,int pt){
        int sum = 0;
        int tmp = num;
        for(int i=1;prime[i]*prime[i]<=tmp;i++){
            if(tmp%prime[i]==0){
                fac[sum++] = prime[i];
                while(tmp%prime[i]==0) tmp/=prime[i];
            }
        }
        if(tmp>1) fac[sum++] = tmp;

        for(int i=0;i<sum;++i){
            int x = num/fac[i];
            if(pos[x]){
                AddEdge(pt,pos[x]);         
                AddEdge(pos[x],pt);
            }
        }
    }

    int main()
    {
        #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
        #endif
        pre();
        int T,cas=1; scanf("%d",&T);
        while(T--){
            int N; scanf("%d",&N);
            init();
            memset(pos,0,sizeof(pos));
            for(int i=1;i<=N;++i){
                scanf("%d",&num[i]);
                pos[num[i]] = i;
            }
            for(int i=1;i<=N;++i){
                ADD(num[i],i);
            }
            nx = ny = N;
            int res= N - MaxMatch()/2;
            printf("Case %d: %d\n",cas++,res);
        }
        return 0;
    }

