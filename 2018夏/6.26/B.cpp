#include<bits/stdc++.h>
using namespace std;
const int maxn =2e5+5;
typedef long long LL;
class Point
{
public:
	Point(int a = 0, int b = 0) :x(a), y(b){ }
	double abs(){ return sqrt(x*x + y*y); }
	LL x, y;
}p[maxn];
typedef Point Vector;

LL cross(Vector &a, Vector &b)  {return a.x*b.y - a.y*b.x;}

LL cross(Point &p0, Point &p1, Point &p2)
{
	Vector a(p1.x - p0.x, p1.y - p0.y);
	Vector b(p2.x - p0.x, p2.y - p0.y);
	return cross(a, b);
}

int main()
{
    int N,x,y;
    while(scanf("%d",&N)==1){
        for(int i=0;i<N;++i){
            scanf("%d%d",&x,&y);
            p[i].x=x;
            p[i].y=y;          
        }
        LL res=__LONG_LONG_MAX__;
        for(int i=0;i<N;++i){
            res = min(res,cross(p[i],p[(i+1)%N],p[(i+2)%N]));
        }
        printf("%lld\n",res);
    }
    return 0;
}
