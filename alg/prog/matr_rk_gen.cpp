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
    cout << "Вычислить ранг матрицы методом элементарных преобразований:\n$$\n" ;
	tex_matrix(B) ;
	cout << "$$\n" ;
	B.gaus1() ;
	cout << "\n%" << k << ' ' << n;
	comment_matrix (B,"step") ;
	cout << "%cols=\n%" ;
	
	cerr << "Ответ:\n\n" ;
	cerr << "$ rk A = " << B.main_vect.size() << "$\n\n" ;
	cerr << "Номера базисных столбцов:\n" ;
	for (int i=0; i<B.main_vect.size(); i++) {
	  if (i>0) cerr << ", " ;
	  cerr << B.main_vect[i]+1  ;
	  cout << B.main_vect[i]+1 << ' '  ;
	}
	cout << "\n%rk=\n%"  << B.main_vect.size() ;
	cerr << "\n\nСтупенчатый вид:\n$$\n" ;
	tex_matrix (B, cerr) ;
	cerr << "$$\n" ;
	comment_matrix (A, "easy", cerr) ;

//	myMatrix C= A.concat(B) ;
//	C.gaus1() ;
//	A.gaus1() ;	
//	A.delim() ;
  
  return 0 ;
}
