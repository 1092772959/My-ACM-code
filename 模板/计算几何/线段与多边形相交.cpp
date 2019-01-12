#include<iostream>
#include<cmath>
#include<iomanip>
#include<stdio.h>
using namespace std;
#define EPS (1e-10)
#define equals(a,b) (fabs(a)-fabs(b)>EPS)
#define COUNTER_CLOCK 1
#define CLOCKWISE -1
#define ONLINE_BACK 2
#define ONLINE_FRONT -2
#define ON_SEGMENT 0
class Point{
public:
	Point(int a = 0, int b = 0) :x(a), y(b){ }
	double abs(){ return sqrt(x*x + y*y); }
	int x, y;
};
Point p[10005],a,b;
int n,count=1;
typedef Point Vector;

double cross( Vector &a, Vector &b) { return a.x*b.y - a.y*b.x;}

double dot(Vector &a, Vector &b) { return a.x*b.x + a.y*b.y;}

double cross(Point &p0, Point &p1, Point &p2)
{
	Vector a(p1.x - p0.x, p1.y - p0.y);
	Vector b(p2.x - p1.x, p2.y - p1.y);
	return cross(a, b);
}

int ccw(Point p0, Point p1, Point p2)
{
	Vector a(p1.x - p0.x, p1.y - p0.y);
	Vector b(p2.x - p0.x, p2.y - p0.y);
	if (cross(a, b) > EPS) return COUNTER_CLOCK;
	if (cross(a, b) < -EPS)return CLOCKWISE;
	if (dot(a, b) < -EPS) return ONLINE_BACK;
	if (a.abs() < b.abs())return ONLINE_FRONT;

	return ON_SEGMENT;
}

bool intersect(Point p1, Point p2, Point p3, Point p4)
{
	return (ccw(p1, p2, p3)*ccw(p1, p2, p4) <= 0 &&
		ccw(p3, p4, p1)*ccw(p3, p4, p2) <= 0);
}

void solve()
{
    if (!n) return;
    bool j = false;
    for (int i = 0; i < n; ++i)
        cin >> p[i].x >> p[i].y;
    cin >> a.x >> a.y >> b.x >> b.y;
    p[n].x = p[0].x;
    p[n].y = p[0].y;
    for (int i = 0; i < n; ++i){
        if (intersect(p[i], p[i + 1], a, b)){
            j = true;
            break;
        }
    }
    printf("Case %d:\n",count++);
    if (j)
        cout << "Yes\n";
    else
        cout << "No\n";
}


