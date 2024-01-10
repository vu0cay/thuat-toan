//https://oj.vnoi.info/problem/kquery
#include <bits/stdc++.h>

#define MAXSIZE 200005
#define Arr_size 30005
#define Pos int
#define val long int
#define el cout<<"\n"

using namespace std;

typedef struct {
	int k;
	int l;
	int r;
} Query;
typedef pair<Query, Pos> QueryType; // luu gia tri va vi tri 
typedef pair<val,Pos> ArrayType; 
vector <ArrayType> a (Arr_size);
int n;
int q; // so truy van
vector <val> b(MAXSIZE);
QueryType que[MAXSIZE];

vector<val> st(Arr_size*4);

bool operator < (const ArrayType& a, const ArrayType& b)
{
	return a.first < b.first;
}
bool operator < (const QueryType& a, const QueryType& b)
{
	return a.first.k < b.first.k ;
}
bool operator >= (const QueryType& a, const QueryType& b)
{
	return a.first.k >= b.first.k;
}
bool operator == (const QueryType& a, const QueryType& b)
{
	return a.first.k == b.first.k;
}
void build(int id,Pos l,Pos r)
{
	if(l == r) {
		st[id] = 1;
		return;
	}
	
	Pos mid = l - (l-r)/2;
	
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
	
	st[id] = st[id*2] + st[id*2+1];
	
}

void update(int id,Pos l,Pos r,Pos i)
{
	if(i<l || i>r) return;
	
	if(l == r) {
		st[id] = 0;

		return;
	}
	
	Pos mid = l - (l-r)/2;
	
	update(id*2,l,mid,i);
	update(id*2+1,mid+1,r,i);
	
	st[id] = st[id*2] + st[id*2+1];

}


val get(int id,Pos l,Pos r,Pos u,Pos v)
{
	if(v<l || u > r) return 0;
	
	if(u<=l && r<=v) {
		return st[id];
	}
	
	Pos mid = l - (l-r)/2;

	return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
}

// quicksort

int Partition(QueryType que[],int l,int r,QueryType pivot)
{
	int i,j;
	i = l;
	j = r;
	
	while(i<j)
	{
		while(que[i] < pivot) i++;
		
		while(que[j] >= pivot) j--;
		
		if(i<j) 
		{

			swap(que[i],que[j]);

		}
	}
	
	
	return i;
}

int FindPivot(QueryType que[],int l,int r)
{
	QueryType firstkey = que[l];
	
	int i = l+1;
	while(que[i] == firstkey && i<=r) i++;
	
	if(i > r) return -1;
	else 
	{
		if(que[i] < firstkey) return l;
		else return i;
	}
	
	// return dia chi chot pivot
}
void quicksort(QueryType que[],int l,int r)
{
	
	int k,pivotindex;
	QueryType pivot;
	pivotindex = FindPivot(que,l,r);

	if(pivotindex != -1)
	{
		
		pivot = que[pivotindex];
		k = Partition(que,l,r,pivot);
		quicksort(que,l,k-1);
		quicksort(que,k,r); 
	}
	
}


void inPut()
{
	cin>>n;
	a.resize(n+1);
	for(int i = 0; i<n; i++){
		cin>>a[i].first;
		a[i].second = i;
	}
	
	cin>>q;
	que[0].first.k = 0;
	que[0].first.l = 0;
	que[0].first.r = 0;
	que[0].second = 0;
	for(Pos i = 1; i<=q; i++){
		cin>>que[i].first.l>>que[i].first.r>>que[i].first.k;
		que[i].second = i;
	}
}

void solve()
{
	quicksort(que,1,q);
	sort(a.begin() - 1,a.end() - 1);
	
	st.resize(n*4);
	build(1,0,n-1);
	
	b.resize(q+1);
	int j = 0;
	for(Pos i = 1; i<=q && j<n; i++){
		while(j < n && ((a[j].first>=que[i-1].first.k) && (a[j].first <= que[i].first.k)) )
		{
			update(1,0,n-1,a[j].second);

			j++;
		}
		b[que[i].second] = get(1,0,n-1,que[i].first.l-1,que[i].first.r-1);	
	
	}

	for(int i = 1; i<=q; i++) {
		cout<<b[i];
		el;
	}
}

int main()
{
	inPut();	
	solve();
	
	return 0;
}
