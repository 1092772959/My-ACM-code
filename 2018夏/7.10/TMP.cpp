
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,m;
struct Point
{
   int score,pen;
   Point(int score_=0,int pen_=0)
   {
       score=score_;
       pen=pen_;
   }
   bool operator<(const Point &b) const
   {
       if(score==b.score) return pen<b.pen;
       else return score>b.score;
   }
}a[maxn],h[maxn];
int p[maxn],t[maxn];
int c[maxn];
int lowbit(int x)
{
    return x&-x;
}
int getsum(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=c[pos];
        pos-=lowbit(pos);
    }
    return ans;
}
void updata(int pos,int v)
{
    while(pos<maxn)
    {
        c[pos]+=v;
        pos+=lowbit(pos);
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    cin>>n>>m;
    int cnt=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&t[i],&p[i]);
        a[t[i]].score++;
        a[t[i]].pen=p[i];
        h[cnt++]=Point(a[t[i]].score,a[t[i]].pen);
    }
    sort(h,h+m);
    updata(m+1,n);
    memset(a,0,sizeof(a));
    for(int i=1;i<=m;i++){
        int tmp=lower_bound(h,h+m,a[t[i]])-h+1;
        updata(tmp,-1);
        a[t[i]].score++;
        a[t[i]].pen=p[i];
        int tmp2=lower_bound(h,h+m,a[t[i]])-h+1;
        updata(tmp2,1);
        int f=lower_bound(h,h+m,a[1])-h+1;
        cout<<getsum(f-1)+1<<endl;
    }
    system("pause");
    return 0;
}