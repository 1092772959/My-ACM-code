#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
int n, h[N<<1], res;
int main() 
{
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        n += n;
        for (int i = 0; i < n; ++i)
            scanf("%d", &h[i]);
        res = 0;
        for (int i = 0; i < n; ++i)
            res = max(res, h[i] + h[n - i - 1]);
        printf("%d\n", res);
    }
    return 0;
}