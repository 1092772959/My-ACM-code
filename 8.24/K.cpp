#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2+10;
const int ways[][2] = {
    {0, 1}, {0, -1},
    {1, 0}, {-1, 0}
};

int N, M;
bool vis[MAXN][MAXN][1<<5];
int Map[MAXN][MAXN];
int id[MAXN][MAXN];

struct Point { int x, y, s, step; };

int main()
{
    while(~scanf("%d%d", &N, &M) && (N || M) )
    {
        memset(vis, 0, sizeof vis);
        memset(id, 0, sizeof id);

        int si, sj, tgt = 0;
        for( int i = 1; i <= N; i++ )
        {
            for( int j = 1; j <= M; j++ )
            {
                scanf("%d", &Map[i][j]);

                if( Map[i][j] == 2)
                    si = i, sj = j;
                else if( Map[i][j] == 1)
                    id[i][j] = tgt++;
            }
        }

        int ans = 0, recs = 0;
        queue<Point> que;
        que.push({si, sj, 0, 0});
        while(!que.empty())
        {
            Point tp = que.front();
            que.pop();

            int &x = tp.x, &y = tp.y;
            int &step = tp.step;
            int &s = tp.s;

            if( x <= 0 || x > N || y <= 0 || y > M) continue;
            if( Map[x][y] < 0 ) continue;
            if( vis[x][y][s] ) continue;

            if( Map[x][y] == 1 )
            {
                s |= (1<<id[x][y]);
            }

            int num = 0;
            for( int i = 0; i < tgt; i++ )
                if( s &(1<<i)) num ++;

            if( num >= tgt ) {
                ans = step; recs = s;
                break;
            }

            vis[x][y][s] = 1;

            for( int k = 0; k < 4; k++ )
            {
                int xx = x + ways[k][0];
                int yy = y + ways[k][1];
                que.push({xx, yy, s, step+1});
            }
        }

        int num = 0;
        for( int i = 0; i < tgt; i++ )
            if( recs &(1<<i)) num ++;

        printf("%d\n", num < tgt? -1: ans);
    }
    return 0;
}