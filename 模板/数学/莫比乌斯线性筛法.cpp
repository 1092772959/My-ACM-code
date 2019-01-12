#include<bits/stdc++.h>
const int maxn=60000+5;
bool vis[maxn];
int prime[maxn],mu[maxn];
void init_mu(int n){
    int cnt=0;
    mu[1]=1;
    for(int i=2;i<n;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<cnt&&i*prime[j]<n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)   {mu[i*prime[j]]=0;break;}
            else { mu[i*prime[j]]=-mu[i];}
        }
    }
}