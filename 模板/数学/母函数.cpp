#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL c1[200],c2[200];
int main()
{
	int n;
	while(scanf("%d",&n)==1){
		for(int i=0;i<=n;i++){
			c1[i]=1;
			c2[i]=0;
		}
		for(int i=2;i<=n;i++){
			for(int j=0;j<=n;j++)
			for(int k=0;k<=n;k+=i){
				c2[j+k]+=c1[j];
			}
			for(int j=0;j<=n;j++){
				c1[j]=c2[j];
				c2[j]=0;
			}
		}
		printf("%lld\n",c1[n]);
	}
	return 0;
}