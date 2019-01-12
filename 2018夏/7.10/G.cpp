#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 1e5+10;
int N, M;

typedef struct Team{
    int idx;
    int score, penalty;
    bool operator> (const Team& o)const{
        if( score == o.score ){
            if( penalty == o.penalty)
                return idx < o.idx;
            else return penalty < o.penalty;
        }
        return score > o.score;
    }
    bool operator< (const Team& o)const{
        if( score == o.score ){
            if( penalty == o.penalty)
                return idx > o.idx;
            else return penalty > o.penalty;
        }
        return score < o.score;
    }
}T;

typedef tree<T, null_type, greater<T>, rb_tree_tag, 
tree_order_statistics_node_update> Rbtree;
Rbtree t;

vector<Team> v;

bool check(int k)
{
    Team tmp = *t.find_by_order(k);
    if( tmp > v[1] ) return 0;
    else return 1; 
}

int main()
{
    while(~scanf("%d%d", &N, &M)){
        t.clear(), v.clear();

        v.resize(N+1);
        for( int i = 1; i <= N ; i++ ){
            v[i] = {i, 0, 0};
            t.insert(v[i]);
        }
        
        while(M--){
            int i, p; 
            scanf("%d%d", &i, &p);
            t.erase(v[i]);
            v[i].score ++, v[i].penalty += p;
            t.insert(v[i]);

            int L = 0, R = N-1, ans= 0;
            while( L <= R ){
                int mid = L + (R-L)/2;
                if(check(mid)){
                    ans = mid+1;
                    R = mid-1;
                }
                else L = mid+1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
