#include <bits/stdc++.h>
using namespace std;

typedef stack<pair<int, int> > Number;
Number c_pair;
void Euclid(int A, int B, int q)
{
	if(A == 1) return;
	
	pair<int,int> b = c_pair.top(); c_pair.pop();	
	pair<int,int> a = c_pair.top(); c_pair.pop();
	
	c_pair.push(b);
	c_pair.push(make_pair(
		a.first - (q*b.first), a.second - (q*b.second)
	));
		
	Euclid(B, A%B, A/B);
}
int Ucll(int a, int b)
{
	if(b == 0) return a;
	else 
		return Ucll(b,a%b);
}
int main()
{
	int A, B; cin >> A >> B;
	if(Ucll(A,B) != 1) cout <<"ko co nghich dao modulo ";
	else{
		// modul form ri = Ayi + Bxi
		c_pair.push(make_pair(1,0));	// init: ri = Ayi => yi = 1, xi = 0 push (1,0)		
		c_pair.push(make_pair(0,1));	// init: ri = Bxi => yi = 0, xi = 1 push(0,1)
		
		Euclid(B,A%B,A/B);				
		
		pair<int, int> ans = c_pair.top();	// get value of bx = 1 (modul n)
		cout <<ans.second <<" ";
	}
		
	return 0;
}
