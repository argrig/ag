#include "mymatr.h"
#include "mytex.h"


int main () {
  myVector empty(0) ;
  size_t k=0, n=0, dep_mask=0, hash_rad=3, hash_max=20, itype=0 ;
  rand_t d1=-3, d2=3 ;
  char cdep_mask[32] ;
  
//  cin >> k >> n >> cdep_mask >> d1 >> d2 >> hash_rad >> hash_max >> itype ;

  if (!k) k = rand()%3+4 ;
  if (!n) n = 11 - k ;
      
  if (!dep_mask) {
	int mm = min(k, n-1) ;
	int dd2 = (1<<n) - 1 ;
	int dd1 = ( 1<<(n-1) ) | (1<<(n-3) ) ;

	if (!itype) itype = rand()%3 +1 ;
	if (itype==3) itype = (rand()%2) ? itype : 2 ;

	if (itype == 3) { // no solusions
  	  do {
		dep_mask = myrand (dd1, dd2) ;
	  } while (wt(dep_mask, n)<mm-2 || wt(dep_mask, n)>mm || !(dep_mask%2) ) ;
	}
	else if (itype == 1) { // one solusion
	  dep_mask = ((1<<mm)-1) << ( n-mm ) ; 
	}
	else if (itype == 2) { //infinite solusions
  	  do {
		dep_mask = myrand (dd1, dd2) ;
	  } while (wt(dep_mask,n)<mm-2 || wt(dep_mask,n)>=mm || dep_mask%2) ;
	}
  }

	myMatrix A (k, n) ;
	A.gen_step(dep_mask, d1, d2) ;
	myMatrix B = A.hash(hash_rad, hash_max) ;
	myMatrix BB = B.transp() ;
    cout	<< "Найти ранг и базис семейства векторов $\\{e_1\\dots e_" << n
			<< "\\}$ и выразить, если возможно, вектор $x$ через базисные векторы"
			<< ":\n$$\n\\begin{array}{l}\n" ;
		for (int i=0; i<n; i++) {
		  cout << "\\vec{e}_" << i+1 <<" = (";
		  for (int j=0; j<k; j++) {
			if(j) cout << ";" ;
			cout << "~" << BB[i][j] ;
		  }
		  cout << "~)\\\\\n" ;
		}
		
	cout	<< "\\end{array}\n$$\n" ;
	myMatrix B1 = B ;
	B1.gaus1() ;
	
	myVector coeff(n,0) ;
	myVector x(k,0) ;
	for (int i=0, j=0; i<n; i++) {
	  if (B1.main_vect[j]==i) {
		coeff[i] = myrand(4) ;
		x += coeff[i]*BB[i] ;
		j++ ;
	  }
	}
	cout << "$\\vec x = (~" ;
	for (int i=0; i<k; i++) {
	  if (i) cout << ";~";
	  cout << x[i] ;
	}
	cout << "~)$" ;


	cout << "\n%" << k << ' ' << n;
	comment_matrix (B1,"step") ;
	cout << "%cols=\n%" ;
	
	cerr << "Ответ:\n\n" ;
	cerr << "Ранг системы векторов равен " << B1.main_vect.size() << "\n\n" ;
	cerr << "Базисные векторы:\n$" ;
	for (int i=0; i<B1.main_vect.size(); i++) {
	  if (i) cerr << ",~" ;
	  cerr << "\\vec{e}_"<< B1.main_vect[i]+1 ;
	  cout << B1.main_vect[i]+1 << ' ' ;
	}
	cerr << "$\n\n" ;
	
	myPolynom E(coeff) ;
	cerr << "$\\vec x = " ; tex_comb(E,0,cerr) ; cerr << "$" ;
	cout << "\n%rk=\n%"  << B1.main_vect.size() ;
	cout << "\n%coeff=\n%" << coeff ;
	cerr << "\n\nСтупенчатый вид:\n$$\n" ;
	tex_matrix (B1, cerr) ;
	cerr << "$$\n" ;
	comment_matrix (A, "easy", cerr) ;
  return 0 ;
}
