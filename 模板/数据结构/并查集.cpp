const int MAXN = 1e5+5;
int fa[MAXN];
int A[MAXN];

void init(){
    for (int i=0;i<MAXN;++i){
        fa[i] = i;
        A[i] = 1;
    }
}

int find(int x){
    if (x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}

bool same(int x, int y){
    return find(x) == find(y);
}

void merge(int x, int y){
    y = find(x);
    y = find(y);
    if (x == y) return;
    fa[x] = y; 
}