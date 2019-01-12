#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
struct SGnode{
    int mx,mn;
}tree[maxn<<4];

void pushup(int root){
    tree[root].mx =max(tree[root<<1].mx,tree[root<<1|1].mx);
    tree[root].mn =min(tree[root<<1].mn,tree[root<<1|1].mn);
}

void build(int root,int L,int R){
    if(L==R){
        tree[L].mx=tree[L].mn=0;
        return;
    }
    int mid =(L+R)>>1;
    build(root<<1,L,mid);
    build(root<<1|1,mid+1,R);
    pushup(root);
}

void update(int root,int L,int R,int pos,int val)
{
    if(L==R && L==pos){
        tree[root].mx =tree[root].mn= val;
        return;
    }
    int mid=(L+R)>>1;
    if(pos<=mid)
        update(root<<1,L,mid,pos,val);
    else
        update(root<<1|1,mid+1,R,pos,val);
    pushup(root);
}

int getmax(int root,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
        return tree[root].mx;
    int mid=(l+r)>>1,res=0;
    if(L<=mid)
        res=max(res,getmax(root<<1,l,mid,L,R));
    if(mid<R)
        res=max(res,getmax(root<<1|1,mid+1,r,L,R));
    return res;
}

int getmin(int root,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
        return tree[root].mn;
    int mid=(l+r)>>1,res=INF;
    if(L<=mid)
        res=min(res,getmin(root<<1,l,mid,L,R));
    if(mid<R)
        res=min(res,getmin(root<<1|1,mid+1,r,L,R));
    return res;
}
