#include <mymatr.h>
#include <mytex.h>

int main () {
	myVector empty(0) ;
	const size_t n=3 ;
	const size_t prime[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97} ; 
	const size_t div1     = prime [rand()%8 + 8]  ;
	const size_t div2     = prime [rand()%8 + 17] ;
	const size_t div_det1 = prime [rand()%7 + 1]  ;
	const size_t div_det2 = prime [rand()%7 + 1]  ;
	const size_t modulo = div1*div2 ;
	const size_t rad = 15 ;
	myMatrix A (n,n,0), A1(n, n);
	myVector x(n), b(n), b1(n);
	A[0][0] = div_det1; A[1][1] = div_det2 ; A[2][2] = div1 ;
	size_t condition=0, counter=0 ;
do {
	condition=0 ;
	// generating A matrix with det = div_det1*dev_det2*div2
	for (size_t i=0; i<n; i++) {
		for (size_t j=0; j<n; j++) {
			if (i<j) {A[i][j] = rand()%rad+1 ;} ;	
		}
	}
	
	// hashing A matrix
	for (size_t i=0; i<n; i++) {
		for (size_t j=0; j<i; j++) {
			A[i] = A[i] - (myScalar)(rand()%rad+1)*A[j] ;
		}
	}
	
	// generating x and b vectors in A*x=b equation
	for(size_t i = 0 ; i<x.size(); i++) {x[i] = rand()%(modulo-1)+1; }
	b=A*x ;
	// generating eqution A1 nx(n+1) matrix
	myMatrix T(n,1); 
	A1=A ;	
	T.subst_col(b,0) ;
	A1 = A1.concat(T,'|') ;

	// bringing all, except b,  to modulo 
	for(size_t i=0; i<A1.size(); i++) {
		x[i]%=modulo ;
		for (size_t j=0; j<A1[0].size(); j++) {
			A1[i][j]%=modulo ;
			if (A1[i][j]<0) {A1[i][j]+=modulo ;} ;
		}
		for (size_t j=0; j<A[0].size(); j++) {
			A[i][j]%=modulo ;
			if (A[i][j]<0) {A[i][j]+=modulo ;} ;
		}

	}
	// testing problem to not be so easy
	b1=A*x ;
	for (size_t i=0; i<b1.size(); i++) {
		b1[i]%=modulo ;
	}
	for (size_t i=0; i<b.size();i++) {
		if(b[i]==b1[i]) {
			condition=1;
			counter++ ;
			break ;
		}
	}
} while (condition == 1) ;

	// problem generation
	cout << "Найти одно решение системы уравнений в кольце $Z_{" << modulo << "}$:\n\n" ;
	tex_equation(A1) ;
	comment_matrix(A, "A") ;
	cout << "%b=\n%" << b1 << endl ;
	comment_matrix(A1, "eqn") ;
	cout << "%x=\n%" << x << endl ;
	cout <<"%mod=\n%" << modulo << endl ;
	cerr << "Ответ:\n\n $$x = " ; tex_vect(x, cerr) ; cerr << "$$\n" ;

	return 0 ;
}

