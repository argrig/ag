#include "mymatr.h"
#include "mytex.h"


int main () {
  myVector empty(0) ;
  size_t k=0, dep_mask=7, hash_rad=3, hash_max=10, itype=0 ;
  rand_t d1=-7, d2=7 ;
  
//  cin >> k >> n >> cdep_mask >> d1 >> d2 >> hash_rad >> hash_max >> itype ;

 	if (!k) k = 3 ;

	myMatrix A (k, k), C(k,k) ;
	do {
		A.gen_rand(d1, d2) ;
	} while (A.det1() == 0) ;

	do {
		C.gen_rand(d1, d2) ;
	} while (C.det1() == 0) ;
	
	myMatrix B = A*C ;
	myVector y("rand", k, d2) ;

	myVector x = C*y ;
	
	myMatrix BB = B.transp() ;
	myMatrix AA = A.transp() ;
//	cout << x << "\n\n" << y << "\n\n" << A << endl << BB << endl << BB.det1() ;
// 	exit (0) ; 

    cout	<< "Найти матрицу перехода от базиса $\\bf e$ к базису $\\bf g$ " 
			<< "и координаты вектора $\\vec{x}$ в базисе {\\bf g}: "
			<< "\n$$\n\\begin{array}{ll}\n" ;
		for (int i=0; i<k; i++) {
		  cout << "\\vec{e}_" << i+1 <<" = (";
		  for (int j=0; j<k; j++) {
			if(j) cout << ";" ;
			cout << "~" << AA[i][j] ;
		  }
		  cout << "~) & " ;

		  cout << "\\vec{g}_" << i+1 <<" = (";
		  for (int j=0; j<k; j++) {
			if(j) cout << ";" ;
			cout << "~" << BB[i][j] ;
		  }
		  cout << "~)\\\\\n" ;
		}
		
	cout	<< "\\end{array}\n$$\n" ;
		
	myPolynom E(x) ;
	cout << "$\\vec x = " ; tex_comb(E) ; cout << "$\n" ;

	cout << "\n%" << k ;
	comment_matrix (A,"col_e") ;
	comment_matrix (B,"col_g") ;
	comment_matrix (C,"trans") ;
	
	myMatrix X=x, Y=y ;
	
	comment_matrix (X, "x") ;
	comment_matrix (Y, "y") ;
		
	cerr << "Ответ:\n\n" ;
	cerr << "Матрица перехода:\n\n$$\n";  tex_matrix(C, cerr); cerr << "$$\n\n" ;
	
	E=y ;
	cerr << "$\\vec{x} = " ; tex_comb(E,0,cerr,'g') ; cerr << "$" ;

  return 0 ;
}
