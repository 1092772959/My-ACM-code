#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define eps 1E-8
/*注意可能会有输出-0.000*/
#define sgn(x) (x<-eps? -1 :x<eps? 0:1)//x为两个浮点数差的比较,注意返回整型
#define cvs(x) (x > 0.0 ? x+eps : x-eps)//浮点数转化
#define zero(x) (((x)>0?(x):-(x))<eps)//判断是否等于0
#define mul(a,b) (a<<b)
#define dir(a,b) (a>>b)
typedef long long ll;
typedef unsigned long long ull;
const int Inf=1<<28;
const ll INF=1ll<<60;
const double Pi=acos(-1.0);
const int Mod=1e9+7;
const int Max=50010;
struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {};
    int read()
    {
        scanf("%lf%lf",&x,&y);
    }
    inline Point operator+(const Point& a)const
    {
        return Point(x+a.x,y+a.y);
    }
    inline Point operator*(double a)const
    {
        return Point(x*a,y*a);
    }
    inline Point operator-(const Point& a)const
    {
        return Point(x-a.x,y-a.y);
    }
    inline bool operator<(const Point& a)const
    {
        return sgn(x-a.x)<0||zero(x-a.x)&&sgn(y-a.y)<0;
    }
    inline bool operator!=(const Point& a)const
    {
        return !(zero(x-a.x)&&zero(y-a.y));
    }
};
typedef Point Vector;
struct Line
{
    Point p;
    Vector v;
    double ang;//极角
    Line() {};
    Line(Point p,Vector v):p(p),v(v)
    {
        ang=atan2(v.y,v.x);
    }
    inline bool operator<(const Line& L)const
    {
        return ang<L.ang;
    }
};
double Dis(Point A,Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
bool OnLeft(Line L,Point p)
{
    return Cross(L.v,p-L.p)>0;
}
Point GetIntersection(Line a,Line b)
{
    Vector u=a.p-b.p;
    double t=Cross(b.v,u)/Cross(a.v,b.v);
    return a.p+a.v*t;
}
int HarfplaneIntersection(Line *L,int n)
{
    sort(L,L+n);
//        for(int i=0; i<n; ++i)
//    {
//        printf("%lf %lf %lf %lf\n",L[i].p.x,L[i].p.y,L[i].v.x,L[i].v.y);
//    }
    int first,last;
    Point *p=new Point[n];
    Line *q=new Line[n];
    q[first=last=0]=L[0];
    for(int i=0; i<n; ++i)
    {
        while(first<last && !OnLeft(L[i],p[last-1])) last--;
        while(first<last && !OnLeft(L[i],p[first])) first++;
        q[++last]=L[i];
        if(zero(Cross(q[last].v,q[last-1].v)))
        {
            last--;
            if(OnLeft(q[last],L[i].p))
                q[last]=L[i];
        }
        if(first<last)
            p[last-1]=GetIntersection(q[last-1],q[last]);
    }
    while(first<last&&!OnLeft(q[first],p[last-1]))
        last--;
//        printf("%d\n",last-first-1);
    delete []p;
    delete []q;
    return max(last-first-1,0);
}
Point tow[Max];
Line convex[Max];
int Solve(int mid,int n)
{
    if(n-mid<=2)//剩余的点
        return 0;
    for(int i=0; i<n; ++i)
    {
        //注意注意，半平面交为逆时针
        convex[i]=Line(tow[i],tow[(i-mid-1+n)%n]-tow[i]);//关键，删除了mid个点后的半平面
    }
    return HarfplaneIntersection(convex,n);
}
int Dichotomy(int lef,int rig,int n)//二分
{
    while(lef<rig)
    {
        int mid=(lef+rig>>1);//代表删多少个点
        if(Solve(mid,n))//非空即为需要删除更多的点
        {
            lef=mid+1;
        }
        else
        {
            rig=mid;
        }
    }
    return lef;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0; i<n; ++i)
        {
            tow[i].read();
        }
        printf("%d\n",Dichotomy(1,n,n));
    }
    return 0;
}