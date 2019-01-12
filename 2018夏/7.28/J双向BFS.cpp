#include<stdio.h>
#include<iostream>
#include<cstring>
#include<iostream>
#include<queue>
#include<map>
#include<string>
#include<stack>
using namespace std;
typedef long long LL;
const int maxn =10;
const int INF=0x3f3f3f3f;
struct Node{
    int step, but;  
    LL pre;
};
map<LL,Node> path;
LL u,v,p;

LL fpow(LL a,LL n)
{
    LL res=1;
    while(n){
        if(n&1) res =(res*a)%p;
        a = a*a %p;
        n>>=1;
    }
    return res;
}

void Print(LL a,LL b,int op)
{
    printf("%d\n",path[a].step-1-path[b].step);
    stack<int> S;
    while(a!=u){
        Node ap = path[a];
        S.push(ap.but);
        a = ap.pre;
    }
    while(!S.empty()){
        int x =S.top();S.pop();
        printf("%d ",x);
    }
    printf("%d ",op);
    while(b!=v){
        Node bp =path[b];
        printf("%d ",bp.but);
        b = bp.pre;
    }
    puts("");
}


void BFS()
{
    path.clear();
    path[u]=(Node){1,-1,-1};
    path[v]=(Node){-1,-1,-1};          
    queue<LL> qf,qb;
    qf.push(u); qb.push(v);
    while(!qf.empty()|| !qb.empty()){
        if(!qf.empty()){
            LL x = qf.front(); qf.pop();
            Node xp = path[x];
            LL next = (x+1)%p;
            Node np = path[next];
            if(np.step==0){         //未访问
                path[next]= (Node){xp.step+1,1,x};
                qf.push(next);
            }
            else if(np.step<0){     //相遇
                Print(x,next,1);
                return;
            }

            next = (x+p-1) %p;              //op2
            np = path[next];
            if(np.step==0){
                path[next]=  (Node){xp.step+1,2,x};
                qf.push(next);
            }
            else if(np.step<0){
                Print(x,next,2);
                return;
            }
            
            next = fpow(x,p-2);
            np = path[next];
            if(np.step==0){
                path[next] = (Node){xp.step+1,3,x};
                qf.push(next);
            }
            else if(np.step<0){
                Print(x,next,3);
                return;
            }
        }

        if(!qb.empty()){
            LL x = qb.front(); qb.pop();
            Node xp = path[x];

            LL next = (x+p-1)%p;
            Node np = path[next];
            if(!np.step){
                path[next] = (Node){xp.step-1,1,x};
                qb.push(next);
            }
            else if(np.step>0){
                Print(next,x,1);
                return;
            }

            next = (x+1)%p;
            np = path[next];
            if(!np.step){
                path[next] = (Node){xp.step-1,2,x};
                qb.push(next);
            }
            else if(np.step>0){
                Print(next,x,2);
                return;
            }

            next = fpow(x,p-2);
            np = path[next];
            if(!np.step){
                path[next] = (Node){xp.step-1,3,x};
                qb.push(next);
            }
            else if(np.step>0){
                Print(next,x,3);
                return;
            }
        }
    }
}

int main()
{
     #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int N,M,tmp,T;
    while(scanf("%lld %lld %lld",&u,&v,&p)==3){
        if(u==v){
            puts("0");
            continue;
        }
        BFS();
    }
    return 0;
}