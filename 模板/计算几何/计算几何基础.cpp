#include<iostream>
#include<cmath>
#include<iomanip>
#include<stdio.h>
using namespace std;
int n;

class Point
{
public:
	Point(int a = 0, int b = 0) :x(a), y(b){ }
	double abs(){ return sqrt(x*x + y*y); }
	int x, y;
};
Point p[10005];
typedef Point Vector;

double cross(Vector &a, Vector &b)
{
	return a.x*b.y - a.y*b.x;
}

double cross(Point &p0, Point &p1, Point &p2)
{
	Vector a(p1.x - p0.x, p1.y - p0.y);
	Vector b(p2.x - p0.x, p2.y - p0.y);
	return cross(a, b);
}

double area()
{
    int i;
    double sum=0;
    for (i = 1; i < n - 1; ++i)
        sum += cross(p[0], p[i], p[i + 1]);
    sum= 0.5 *abs(sum);
    return sum;
}

void shape()
{
    bool j= true;
    p[n].x = p[0].x;//p[n+1].x = p[1].x;//p[n+1].y = p[1].y;
    p[n].y = p[0].y;//p[n+2].x = p[2].x;//p[n+2].y = p[2].y;
    for (int i = 1; i <= n&&j; ++i)     //此处可以忽略点的顺序是顺时针还是逆时针
    {
        if (cross(p[(i - 1)%n], p[i%n], p[(i + 1)%n]) *cross(p[i%n],p[(i+1)%n],p[(i+2)%n])<0)
            j = false;
    }
    if (j)
        cout << "Convex\n";
    else
        cout << "Concave\n";
}

int gcd ( int a,int b){
	if(b==0) return a;
	else return gcd(b,a%b);
}

int OnSegment(Point A,Point B){
	 return gcd(fabs(A.x-B.x),fabs(A.y-B.y))+1;         //线段上格点的个数
}

int pointOnEdge()                   //多边形边上的整点
{
    int res=0;
    for(int i=0;i<n;++i)
        res+=OnSegment(p[i],p[(i+1)%n]);
    return res-n;               //每条边都多算了一个点
}

int InSide(){
// area是面积                                  //多边形内部的整点
        return area()-pointOnEdge()/2+1;
}


