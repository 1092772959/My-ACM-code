#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

#define LOCAL
int main() {
  int T;
  #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
  #endif
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> ends(n,-1);
    for (int i = 0; i < n; ++i) ends[i] = i;    
    for (int i = 0; i < m; ++i) {
      int l, r;
      scanf("%d%d", &l, &r);
      ends[l - 1] = max(ends[l - 1], r - 1);            //维护每个点需要处理到的最右的位置        
    }
    set<int> unused;
    for (int i = 1; i <= n; ++i)  unused.insert(i);     //一开始1-N的值都是可以使用的
    vector<int> ret(n);
    int l = 0, r = -1;                  //指针L和指针R
    for (int i = 0; i < n; ++i){
      if (r >= ends[i]) continue;
      while (l < i)   unused.insert(ret[l++]);          //将可以使用的数值重新加入集合 
      while (r < ends[i]){ 
        ret[++r] = *unused.begin();                     //将最小值加入结果中
        unused.erase(ret[r]);                           //在集合中删去
      }
    }
    for (int i = 0; i < n-1; ++i)   printf("%d ", ret[i]);
    printf("%d\n",ret[n-1]);
  }
  return 0;
}
