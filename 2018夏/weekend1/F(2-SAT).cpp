#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+7;  
struct node  
{  
    int v,next;  
}edge[MAXN];
int head[MAXN],index;  

void add_edge(int u,int v)          //前向星
{  
    edge[index].v=v;  
    edge[index].next=head[u];  
    head[u]=index++;  
}  
int DFN[MAXN],low[MAXN],stack_[MAXN],in_stack[MAXN],belong[MAXN];  
int cir,top,temp;  

void Tarjan(int u)  
{  
    int p;  
    DFN[u]=low[u]=++temp;  
    in_stack[u]=1;  
    stack_[top++]=u;  
    for(int i=head[u]; i+1; i=edge[i].next)  {  
        int v=edge[i].v;  
        if(!DFN[v]){  
            Tarjan(v);  
            low[u]=min(low[u],low[v]);  
        }  
        else if(in_stack[v])    
            low[u]=min(low[u],DFN[v]);    
    }  
    if(low[u]==DFN[u])  {  
        ++cir;  
        do{  
            p=stack_[--top];  
            in_stack[p]=0;  
            belong[p]=cir;  
        }while(p!=u);  
    }  
}  

int main()
{
    int n,m,a,b,c,d;
    while(scanf("%d",&n)==1){
        temp=index=cir=top=0;
        memset(head,-1,sizeof(head));
        memset(DFN,0,sizeof(DFN)); 
        memset(in_stack,0,sizeof(in_stack));
        scanf("%d",&m);
        for(int i=0;i<m;++i){
            scanf("%d%d%d%d",&a,&b,&c,&d);
            a =(a<<1) +c;
            b =(b<<1) +d;
            add_edge(a,b^1);
            add_edge(b,a^1);
        }
        for(int i=0;i< (n<<1);++i){
            if(!DFN[i])
                Tarjan(i);
        }
        bool flag = false;
        for(int i=0;i<n && !flag;++i){
            if(belong[i<<1]==belong[(i<<1)^1])
                flag = true;
        }
        if(flag) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}