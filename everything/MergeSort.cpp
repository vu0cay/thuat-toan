// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
using namespace std;

void Merge(int x[], int y[], int l, int mid, int r)
{
    int L[mid - l + 1];
    int R[r - mid];

    for(int i = 0; i < mid - l + 1; i++) L[i] = x[i + l];
    for(int i = 0; i < r - mid; i++) R[i] = x[i + mid + 1];

    int i = 0,j = 0, k = l;

    while(i < mid - l + 1 && j < r-mid)
    {
        if(L[i] < R[j])
        {
            y[k] = L[i];
            i++;
        }
        else
        {
            y[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < mid - l + 1 )
    {
        y[k] = L[i];
        i++;
        k++;
    }
    while(j < r-mid)
    {
        y[k] = R[j];
        k++;
        j++;
    }

}
/**
void MergeSort(int a[], int l, int r)
{
    if(l == r) return;

    int mid = (l+r)/2;

    MergeSort(a,l, mid);
    MergeSort(a,mid + 1, r);

    Merge(a,l,mid,r);
}
**/
void MergeLength(int x[], int y[], int len, int n)
{
    int l = 0, mid = len - 1, r = (len*2) - 1;
    while(r < n)
    {
        Merge(x,y,l,mid,r);
        l = l + (len*2);
        mid = mid + (len*2);
        r = r + (len*2);
    }
    if(mid < n - 1) Merge(x,y,l,mid,n-1);
    else
        if(l < n)
        {
            for(int i = l; i<n; i++) y[i] = x[i];
        }
}
int main() {

    int a[] = {1,3,123,1244,421,4,3,123,4,12,41,24,124};
    int n = sizeof(a)/sizeof(int);
    for(auto e : a) cout << e <<" ";
    cout << endl;
    int tmp[n];
    int len = 1;
    int flag = 1;
    while(len < n)
    {
        if(flag)
            MergeLength(a,tmp,len,n);
        else
            MergeLength(tmp,a,len,n);
        len = len*2;
        flag = !flag;
    }
    cout << flag <<endl;
    if(!flag)
        for(auto e : tmp) cout << e <<" ";
    else
        for(auto e : a) cout << e <<" ";

    return 0;
}
