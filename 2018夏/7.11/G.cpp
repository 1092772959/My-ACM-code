#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
int cnt[30]={0,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,0};
bool bonus(int lev,int consec)
{
    if(6<=lev && lev<=25 && consec>=3) return true;
    else return false;
}

void win(int &lev,int &star,int &consec)
{
    consec++;
    star++;
    if(bonus(lev,consec)) 
        star++;
    int limit = cnt[lev];
    if(star>limit){
        star=star-limit;lev--;
    }
}

void lose(int &lev,int &star)
{
    if(lev>20) return;
    if(lev==20 && star==0) return;
    star--;
    if(star<0){
        lev++;
        star = cnt[lev]-1;
    }
}

int main()
{
    string op;
    while(cin>>op){
        int lev =25, star=0;
        int consec=0;
        char o;
        for(int i=0;i<op.size();++i){
            o=op[i];
            if(o=='W'){  //win
                win(lev,star,consec);
                if(lev==0) break;            
            }
            else{   //lose
                consec=0;
                lose(lev,star);
            }
        }
        if(lev==0) printf("Legend\n");
        else printf("%d\n",lev);
    }
    return 0;
}