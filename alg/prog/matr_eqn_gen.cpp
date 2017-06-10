#include "mymatr.h"
#include "mytex.h"

int main () {
rand_t nxn, xleft, diap1, diap2, max_det ;
	myVector empty ;
cin >> nxn >> xleft >> diap1 >> diap2 >> max_det;
nxn = (nxn) ? nxn : 3 ;
if (nxn == -1) nxn=rand()%3 + 2 ;
diap1 = (diap1) ? diap1 : -7 ;
diap2 = (diap2) ? diap2 : 7 ;
max_det = (max_det) ? max_det : 5 ;
//LAST EDITION :
xleft = rand()%2 ;

	myMatrix A(nxn, nxn) ;
	myScalar det ; 

	do {
		A.gen_rand(diap1, diap2) ;
		det = A.det1();
	} while ( ! ( det!=0 && abs(det) < max_det ) ) ;

	myMatrix B(nxn, nxn) ;
	myMatrix X("rand", nxn, nxn, diap1, diap2) ;

		B = (xleft) ? X*A : A*X ;

	cout << "Решить матричное уравнение:\n$$\n" ;
	if (xleft) cout << "X " ;
	tex_matrix(A) ;
	const char *sign = (xleft) ? " = " : "X = " ;
	cout << sign ; 
	tex_matrix(B) ;
	cout << "$$\n" ; 

	comment_matrix (X,"X") ;
	myMatrix D=A.rvs() ;
	comment_matrix (D ,"rvs") ;
	cout << "\n%det=\n%" << D[0].idenom << endl ;

	cerr << "Ответ:\n$$\n" ;
	cerr << "X = " ;
	tex_matrix(X, cerr) ;
	cerr << ",\\quad A^{-1} = \\frac{1}{" << D[0].idenom << "}" ;
	tex_matrix(D, cerr) ;
	cerr << "$$\n" ;
	
}
