#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
using namespace std;
typedef long long ll;
bool Check(vector <ll> r, vector <ll> a, ll x){
	int i;
	ll k;
	int n = a.size();
	for(i = 0 ; i < n ; i++){
		k = x;
		if(k < 0){
			k = k % a[i] + a[i];
		}
		else {
			k %= a[i];
		}
		if(r[i] != k){
			return false;
		}
	}
	return true;
}
int main(){
	int i, k;
	int n;
	ll x;
	vector <ll> a;
	vector <ll> r;
	//Schitivaem kolichestvo uravneniy
	cin >> n;
	//Schitivaem samo reshenie
	cin >> x;
	//Schitivaem posledovatelnost x[]
	for(i = 0 ; i < n ; i++){
		cin >> k;
		r.push_back(k);
	}
	//Schitivaem posledovatelnost a[]
	for(i = 0 ; i < n ; i++){
		cin >> k;
		a.push_back(k);
	}
	if(Check(r, a, x) == true){
		cout << 1 << endl;
	}
	else {
		cout << -1 << endl;
	}
	return (0);
}
