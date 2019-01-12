#include<bits/stdc++.h>
using namespace std;
const int maxn =1e4+5;
const int maxv = 1e6+5;
int a[maxn];
int cnt[maxv];
int n,num;

int main()
{
    while(~scanf("%d",&n),n){
        memset(cnt,0,sizeof(cnt));
        num=0;
        for(int i=0;i<n;++i){
            scanf("%d",&a[i]);
            cnt[a[i]]++;
            num = max(cnt[a[i]],num);
        }
        sort(a,a+n);
        cout<<num<<endl;
        for(int i=0;i<num;i++)  {  
            for(int j=i;j<n;j+=num){  
                if(j!=i)  
                    cout<<" ";  
                cout<<a[j];  
            }  
            cout<<endl;  
        }  
        cout<<endl;
    }    
    return 0;
}
