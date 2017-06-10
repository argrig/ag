#include "mymatr.h"
#include "mytex.h"
#include <bitset>

int main () {
  myVector empty(0) ;
  size_t k1=0, k2=0, n=6, dep_mask1=0, dep_mask2=0, hash_rad=3, hash_max=20;
  rand_t d1=-3, d2=3 ;
  char cdep_mask[32] ;
  
//  cin >> ;
// parameters
size_t dim_sum = rand()%2+4 	; // set sum dimention to 4 or 5
if (rand()%7 == 1) dim_sum = 6	; // set sum dimention to 6 with prob 1/7
size_t dim_its=rand()%2+1 		;// set intersection dimention to 1 or 2
if ( dim_sum>4 && rand()%2==1 ) dim_its = 3 ; // set dim_its=3 with prob 9/28
size_t dim_dir	= dim_sum + dim_its ;
size_t dim1		= rand()%(dim_dir-2*dim_its-1)+dim_its+1 ; // set dim L_1 > dim_its with dim L_2>dim_its
size_t dim2		= dim_dir - dim1  ; // obvious
size_t tmp		= 9 - dim1 - dim2 ;
if (tmp > 0) {
  size_t tmp0 = rand()%tmp	;
  size_t tmp1 = min(tmp0, tmp-tmp0)	;
  size_t tmp2 = max(tmp0, tmp-tmp0) ;
  if (dim1>dim2) {
	k1 = tmp1 + dim1 ;
	k2 = tmp2 + dim2 ;
  }
  else {
	k1 = tmp2 + dim1 ;
	k2 = tmp1 + dim2 ;	
  }
}
else {
  k1 = dim1 ;
  k2 = dim2 ;
}
//end parameters

myMatrix	L1(k1, n), L2(k2, n), L_sum(dim_sum, n), 
			L_its(dim_its, n), LT1(n,k1), LT2(n,k2) ;

bitset<6> depm1, depm2 ;
do {
  depm1 = rand()%(1<<k1) ;
} while ( !(depm1.count()==dim1 && depm1.test(k1-1)) ) ;
dep_mask1 = depm1.to_ulong() ;

do {
  depm2 = rand()%(1<<k2) ;
} while ( !(depm2.count()==dim2 && depm2.test(k2-1)) ) ;
dep_mask2 = depm2.to_ulong() ;

// cout << dim_sum << '\t' << dim_its << '\t' << dim1 
//		<< '\t' << dim2 << '\t' << k1 << '\t' << k2 << '\t' << depm1 << '\t' << depm2 << "\n\n";

do {
  L_its.gen_rand() ;
} while (L_its.rk()<dim_its) ;

LT1.gen_step(dep_mask1, d1, d2) ;
LT1.gaus1() ;
LT2.gen_step(dep_mask2, d1, d2) ;
LT2.gaus1() ;

L1 = LT1.transp() ;
L2 = LT2.transp() ;

for (size_t i=0; i<dim1; i++) {
  L1[LT1.main_vect[i]]=L_its[i] ;
}

for (size_t i=0; i<dim2; i++) {
  L2[LT2.main_vect[i]]=L_its[i] ;
}

L1 = L1.hash(hash_rad, hash_max) ;
L2 = L2.hash(hash_rad, hash_max) ;

//cout << (LT1.rk()==dim1) << (LT2.rk()==dim2) <<  ; exit(0) ;

myMatrix L_tmp = L1.concat(L2, '-') ;
myMatrix T_sum = L_tmp.transp() ;
T_sum.gaus1() ;

cout << (T_sum.rk()==dim_sum)   ; exit(0) ;

cout << T_sum.main_vect.size() << '\t' << dim_sum << endl ; 
for (size_t i=0; i<T_sum.main_vect.size(); i++) {cout << T_sum.main_vect[i] ;}
exit(0) ;

for (size_t i=0; i<T_sum.main_vect.size(); i++) {
  L_sum[i] = L_tmp[T_sum.main_vect[i]] ;
}


cout	<< L1 << (L1.rk()) << endl << L2 << (L2.rk()) << endl << T_sum << (T_sum.rk()) << endl 
		<< L_sum << (L_sum.rk()) ;

/*
    cout	<< "Найти целочисленные базисы и размерности подпространств "
			<< "$L_1$, $L_2$, $L_1\\cup L_2$, "
			<< "$L_1+L_2$, если $L_1$ порождается векторами $e_i$, $L_2 -$ векторами $f_j$ "
		for (int i=0; i<n; i++) {
		  cout << "\\vec{e}_" << i+1 <<" = (";
		  for (int j=0; j<k; j++) {
			if(j) cout << ";" ;
			cout << "~" << BB[i][j] ;
		  }
		  cout << "~)\\\\\n" ;
		}
		
	cout	<< "\\end{array}\n$$\n" ;
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
*/	

  return 0 ;
}
