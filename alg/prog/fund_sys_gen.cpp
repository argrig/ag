#include "myalgo.h"
#include "mytex.h"

int main () {
  myVector empty(0) ;
  size_t k=0, n=0, dep_mask=0, hash_rad=3, hash_max=20, itype=2 ;
  rand_t d1=-3, d2=3 ;
  char cdep_mask[32] ;
  
//  cin >> k >> n >> cdep_mask >> d1 >> d2 >> hash_rad >> hash_max >> itype ;

  if (!k) k = rand()%2+4 ; // 4 or 5 equations
  if (!n) n = 11 - k ; // 6 or 5 variables 
      
  if (!dep_mask) {
	int mm = min(k, n-1) ;
	int dd2 = (1<<n) - 1 ;
	int dd1 = ( 1<<(n-1) ) | (1<<(n-3) ) ;

	if (itype == 2) { //infinite solusions
  	  do {
		dep_mask = myrand (dd1, dd2) ;
	  } while (wt(dep_mask,n)<mm-3 || wt(dep_mask,n)>=mm-1 || dep_mask%2) ;
	}
  }

	myMatrix A (k, n) ;
	A.gen_step(dep_mask, d1, d2) ;
	myMatrix B = A.hash(hash_rad, hash_max) ;
	myMatrix B1=B ;
	B1.del_col(n-1) ;
	myVector x ("rand", n-1, 7) ;
	myVector y = B1*x ;
	B.subst_col (y,n-1) ;
    cout<< "Найти целочисленное частное решение неоднородной системы и "
		<< "целочисленную фундаментальную систему решений соответствующей однородной системы:\n" ;
	tex_equation(B) ;
// Solution

  B.gaus1() ;
  size_t rk = B.main_vect.size() ;
  size_t df = n-1-rk ;
  myVector v_df(df,0) ;
  cnt_vect_t v_rk = B.main_vect ;
  int cnt_df=0, cnt_rk=0 ;
  for (int i=0; i<n-1; i++) {
	if(i==v_rk[cnt_rk]) { cnt_rk++; }
	else {
	  v_df[cnt_df]=i ;
	  cnt_df++ ;
	}
  }
	
	myMatrix B_short = B ; //added

	B_short.del_col (B_short[0].size() - 1) ; // added
	B_short.gaus1() ; //added
	
	cout << "\n%kn=\n%" << k << ' ' << n;
	comment_matrix (B,"step") ;
	cout << "%cols=\n%" ;
	
	cerr << "Ответ:\n\n" ;
	
	size_t rk_sys = B_short.main_vect.size() ; //added

	myMatrix null_sp = null_space (B_short) ; //new
	
	cerr << "дефект ситстемы: " << df << "\n\n" ; //changed
	cerr << "Свободные неизвестные:\n" ;
	for (int i=0; i<df; i++) {
	  if (i) cerr << ", " ;
	  cerr << "$x_" << v_df[i]+1 << "$" ;
	  cout << v_df[i]+1 << ' ' ;
	}
	cout << "\n%df=\n%"  << df ;
	cerr << "\n\nСтупенчатый вид:\n$$\n" ;
	tex_matrix (B, cerr) ;
	cerr << "$$\n" ;
	cerr << "\nФундаментальная система решений:\n\\begin {eqnarray*}\n" ;
	for (int i=0; i<null_sp.size(); i++) {
	  cerr << "e_" << (i+1) << "&=&" ; 
	  tex_vect(null_sp[i], cerr) ;
	  cerr << "\\\\\n" ;
	}
	cerr << "\\end {eqnarray*}\n" ;
	cerr << "\nОдно из решений:\n$$\n" ;
	myMatrix xx(1,n-1) ;
	xx[0] = x ;
	tex_matrix (xx, cerr) ;
	comment_matrix(xx,"x") ;
	cerr << "$$\n" ;
  return 0 ;
}
