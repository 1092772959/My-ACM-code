
/*

https://blog.csdn.net/outer_form/article/details/51893048
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4+5;
int arr[45][45];
int num[45][45];
vector<int> edges[maxn];
bool vis[maxn], ban[maxn];
int linker[maxn];

bool dfs(int i) 
{
    if(ban[i]) return false;
    for (int j = 0; j < edges[i].size(); j++) {
        int k = edges[i][j];
        if (!vis[k] && !ban[k]) {
            vis[k] = 1;
            if (!linker[k] || dfs(linker[k])){
                linker[k] = i;
                linker[i] = k;
                return true;
            }
        }
    }
    return false;
}

int ans[10005];
int main() {
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    int x, y, n, m, tot=0,k;
    scanf("%d %d", &n, &m);
    char str[45];
    for (int i = 1; i <= n; i++) {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; j++) {
            if (str[j] == 'O') arr[i][j] = 1;
            else if (str[j] == 'X') arr[i][j] = 2;
            else arr[i][j] = 2, x = i, y = j;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (arr[i][j] == 1 ^ (((i + j) & 1) == ((x + y) & 1)))
                num[i][j] = ++tot;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!num[i][j]) continue;
            if(num[i + 1][j]) {
                edges[num[i][j]].push_back(num[i + 1][j]);
                edges[num[i + 1][j]].push_back(num[i][j]);
            }
            if(num[i][j + 1]) {
                edges[num[i][j]].push_back(num[i][j + 1]);
                edges[num[i][j + 1]].push_back(num[i][j]);
            }
        }
    }
    for (int i = 1; i <= tot; i++) {
        memset(vis, 0, sizeof(vis));
        if (!linker[i]) dfs(i);
    }
    scanf("%d", &k);
    for (int i = 1; i <= (k << 1); i++) {
        int tmp = num[x][y];
        ban[tmp] = 1;                           //将该点从图中删除
        if (linker[tmp]) {
            int match = linker[tmp];
            linker[match] = linker[tmp] = 0;
            memset(vis, 0, sizeof(vis));
            ans[i] = (!dfs(match));             //匹配成功表明 起点不一定在最大匹配中，则后手胜              
        }
        scanf("%d%d",&x,&y);
    }
    int res = 0;
    for (int i = 1; i <= k; i++)
        res += (ans[i*2 - 1]&ans[i * 2]);
    
    printf("%d\n", res);
    for (int i = 1; i <= k; i++) {
        if (ans[i*2-1]&ans[i*2]) {
            printf("%d\n", i);
        }
    }
    return 0;
}
