#include<bits/stdc++.h>
using namespace std;
const int maxn =505;
int L[maxn],M[maxn],N[maxn],S;
int a,b,c;

int main()
{  
    int T=1,tmp;
    while(scanf("%d%d%d",&a,&b,&c)==3){
        for(int i=0;i<a;++i)
            scanf("%d",&L[i]);
        for(int i=0;i<b;++i)
            scanf("%d",&M[i]);
        for(int i=0;i<c;++i)
            scanf("%d",&N[i]);
        vector<int> v1;
        for(int i=0;i<a;++i){
            for(int j=0;j<b;++j){
                v1.push_back(L[i]+M[j]);
            }
        }
        sort(v1.begin(),v1.end());
        v1.erase(unique(v1.begin(), v1.end()), v1.end());   //去重
        scanf("%d",&S);
        printf("Case %d:\n",T++);
        while(S--){
            bool flag = false;
            scanf("%d",&tmp);
            for(int i=0;i<c;++i){
                if(binary_search(v1.begin(),v1.end(),tmp-N[i])){
                    flag = true;
                    break;
                }
            }
            if(flag) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}

