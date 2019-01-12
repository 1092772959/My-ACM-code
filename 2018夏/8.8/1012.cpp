#include <bits/stdc++.h>
using namespace std;
const double G = 9.8;

int main()
{
    int T; cin >> T;
    while(T--)
    {
        int a, b, x, y;
        cin >> a >> b >> x >> y;

        double sina = b/sqrt(a*a+b*b);
        double cosa = a/sqrt(a*a+b*b);
        double tana = b*1.0/a;

        double s = (y-tana*(-x)) *sina + (-x)/cosa;
        double sy = (y-tana*(-x)) *cosa;

        double T = sqrt(8*sy/cosa);
        double t = sqrt(2*s/sina);

        int ans = 0;
        if( 0.5* T <= t ){
            ans = 1;
            t -= 0.5* T;
            ans += t/T;
        }

        printf("%d\n", ans);
    }
    return 0;
}