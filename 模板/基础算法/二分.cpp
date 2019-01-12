#include<bits/stdc++.h>

int lower_bound(int *A,int l,int r,int val)
{
    int L=l,R=r,mid,ans=-1;
    while(L<=R){
        mid = L+(R-L)/2;
        if(A[mid]>=val){
            ans = mid;
            R = mid-1;
        }
        else L=mid+1;
    }
    return ans;
}

int upper_bound(int *A,int l,int r,int val)
{
    int L=l,R=r,mid,ans=-1;
    while(L<=R){
        mid = L+(R-L)/2;
        if(A[mid]>val){
            ans = mid;
            R = mid-1;
        }
        else L=mid+1;
    }
    return ans;
}
