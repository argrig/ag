#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
ll gcd(ll a, ll b){
	if(b == 0){
		return (a);
	}
	return gcd(b, a % b);
}
ll Euclid (ll a,ll  b,ll &x,ll &y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return (b);
	}
	ll x1, y1;
	ll nod = Euclid (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return (nod);
}
ll findSolution(ll a1,ll mod1,ll a2,ll mod2){
	ll x,y;
	ll d = Euclid(mod1, mod2, x, y);
	return (mod1 * x * a2 + mod2 * y * a1);
 }
ll solve(vector <ll> a, vector <ll> r){
	ll i,j;
	ll x,y;
	ll total = 0;
	ll nok = 1;//izmenenie
	for(i = 0; i < a.size() ;i++){
		ll tmp=1;
		nok *= a[i];//izmenenie
		for(j = 0; j < a.size(); j++){
			if(i!=j){
				tmp *= a[j];
			}
		}
		total += r[i] * findSolution(1, a[i], 0, tmp);
	}
	//izmenenie
	if(total < 0){
		total = total %nok +nok;
	}
	return total;
}
int main(){
  FILE *rf = fopen("/dev/urandom","r") ;
  srand(((ui)getc(rf)+1)*((ui)getc(rf)+1)*((ui)getc(rf)+1)*((ui)getc(rf)+1)) ;
  int n ;
	int a_min,a_max;
	int x_min,x_max;
	int i, j, k;
	bool p = true;
	char zapyataya;

	//Schtitivaem n a_min a_max x_min x_max
	cin >> n >> a_min >> a_max >> x_min >> x_max ;
	if(a_min == a_max && a_max == x_min && x_min == x_max && x_max == 0){
		a_min = 100;
		a_max = 200;
		x_min = 20;
		x_max = 90;
	}
	vector <ll> a;
	vector <ll> r;
	//Generiruem posledovatelnost a[],v intervale [a_min,a_max]
	k = rand() % (a_max - a_min + 1) + a_min;
	a.push_back( k );
	while(a.size() != n){
		p = true ;
		k=rand() % (a_max - a_min + 1) + a_min;
		for(j = 0 ; j < a.size(); j++){
			if(gcd(k, a[j]) != 1){
				p=false;
				break;
			}
		}
		if(p){
			a.push_back(k);
		}
	}
	//Generiruem posledovatelnost x[],v intervale [x_min,x_max]
  p=true ;
	for (i = 0 ; i < n ; i++){
		k = rand() % (x_max - x_min + 1) + x_min;
    for (int j=0 ; j<i ; j++) {
      if (r[j]==k) {
        i-- ;
        p=false ;
      }
    }
		if (p) { r.push_back(k); }
    p=true ;
	}
	char c = ',';
	//Vivodim s sootvetstvuyushem formate
	cout << n << c << solve(a, r) << c;
	//Posledovatelnost x[]
	for(i = 0 ; i < n; i++){
		cout << r[i] ;
		if(i != n-1){
			cout << " ";
		}
	}
	cout << c;
	//Posledovatelnost a[]
	for(i = 0 ; i < n; i++){
		cout << a[i] <<" ";
	}
	return 0;
}
