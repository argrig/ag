#include "myqvect.h"
#include "mymatr.h"

myQVect get_solution(myMatrix A, cnt_vect_t fr_vect) { 
//Gives the solusion of system with given vector of free variables fr_vect
//A *MUST* be previously gaussed !!!
	size_t rk = A.main_vect.size() ;
	size_t  n = A[0].size() - 1 ;
	size_t  k = A.size() ;
	size_t  r = n-rk ;

	myQVect ans(n, 0) ;
	int eqn_cnt = k-1 ;
	int main_cnt = rk-1 ;
	int fr_cnt = r-1 ;
	for (int var_cnt=n-1; var_cnt>=0; var_cnt--) {
		if (A.main_vect[main_cnt] == var_cnt) {
			if (main_cnt > 0) main_cnt-- ;
			while (A[eqn_cnt][var_cnt]==0) {
				if(eqn_cnt==0) {
					cerr << "can't get solutiuon .... \n" ;
					exit (1) ;
				}
				eqn_cnt-- ;
			}
			ans[var_cnt]=A[eqn_cnt][n] ;
			for (size_t i=n-1; i>var_cnt; i--) {
				ans[var_cnt] -= A[eqn_cnt][i]*ans[i] ;
			}
			ans[var_cnt]/=A[eqn_cnt][var_cnt] ;
			eqn_cnt-- ;
		}
		else {
			ans[var_cnt] = fr_vect[fr_cnt] ;
			fr_cnt-- ;
		}
	}

	return  ans ;
};

myMatrix null_space (myMatrix A) {
	A.gaus1() ;
	size_t rk = A.main_vect.size() ;
	size_t  n = A[0].size() ;
	size_t  k = A.size() ;
	size_t  r = n-rk ;

	if (!r) {
		myMatrix Ker(1, 1) ;
		Ker[0][0]=0 ;
		return Ker ;
	}

	myMatrix Ker (r, n) ;
	myQVect ker (n) ;
	
	for (size_t i=0; i<k; i++) A[i].push_back(0) ;
	
	for (size_t row=0; row<r; row++) {
		cnt_vect_t fr_vect(r, 0) ;
		fr_vect[row] = 1 ;
		ker = get_solution (A, fr_vect) ;
		myQScal ker_prod=1 ;
		for (size_t i=0; i<n; i++) {
			if (ker[i] != 0) { ker_prod*=ker[i]; }
		}
		myScalar nok = ker_prod.get_den() ;
		for (size_t i=0; i<n; i++) { Ker[row][i] = ker[i]*nok; }
		Ker[row].socr() ;
	}
	return Ker ;
}

int main () {
	int k, n ;
	cin >> k >> n ;
	myMatrix a(k, n) ;
	cin >> a ;
	myMatrix b = null_space(a) ;
	cout << a << endl << b ;

  return 0;				
}
