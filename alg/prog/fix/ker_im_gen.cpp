#include "mymatr.h"
#include "mytex.h"
#include "myalgo.h"

#define DIM 6
#define ABS_MAX 30

int main () {
  myVector empty(0) ;
  size_t hash_rad=3, hash_max=20;
  rand_t d1=-2, d2=2 ;
  char cdep_mask[32] ;
  
//  cin >> ;
// parameters
size_t dim_sum = rand()%2+4 	; // set sum dimention to 4 or 5
size_t dim_its = DIM-dim_sum 	; // set intersection dimention
size_t dim_ker ; 
// set kernel dimention to 2-4 but less than dim_sum : 
do { dim_ker = dim_its + rand()%2 + 1 ; } while (dim_ker >= dim_sum) ; 
size_t dim_im  = DIM - dim_ker ; // set image dimention to dim space - dim ker
myScalar test_nod ;
// end parameters

myMatrix Ker(dim_ker, DIM,0), Im(dim_im, DIM,0), Sum(dim_sum, DIM,0), Its(dim_its, DIM,0), 
	 Add_ker(dim_ker-dim_its, DIM,0), Add_im(dim_im-dim_its, DIM,0), F(DIM,DIM,0), Nullsp, Nullim ;
do {
  do {
  	Its.gen_rand(d1,d2) ;
  	Add_ker.gen_rand(d1,d2) ;
  	Add_im.gen_rand(d1,d2) ;
  	Ker=Its.concat(Add_ker) ;
  	Im=Its.concat(Add_im) ;
  } while (Its.rk() != dim_its || Ker.rk() != dim_ker || Im.rk() != dim_im ||
	(Ker.concat(Im)).rk() != dim_sum) ;
  
 Sum = Ker.concat(Add_im) ; 
  
  //cout << "its\n" << Its << (Its.rk()) << "add_ker\n" << Add_ker <<  "add_im\n" << Add_im << "ker\n" 
  //<< Ker << Ker.rk() <<  "im\n" << Im << Im.rk() << "sum" <<  (Ker.concat(Im)).rk() << endl ;
 
  Nullsp = null_space(Ker) ; 
  myMatrix C = Nullsp.concat(Ker) ; // transfer matrix TRANSPONED
  myMatrix Z(dim_ker, DIM, 0) ; // zero matrix
  myMatrix A = Im.concat(Z) ; // operator matrix in Ker-Nullspace basis TRANSPONED
  F = (C.rvs()*A).transp() ; // final operator matrix
  myVector Nod(0) ;
  //making divizion by row nods nod :
  for (size_t i=0; i<F.size(); i++) {
	Nod.push_back(F[i].nod()) ;
  }
  test_nod = Nod.nod() ;
  for (size_t i=0; i<F.size(); i++) {
	F[i] = F[i] / test_nod ;
  }
} while (F.abs_max()>ABS_MAX || F.has_null_col() || F.has_null_row()) ;  

cout	<< "Найти размерность, порождающую и проверочную матрицы ядра и образа линейного оператора, "
	<< "а также размерность и порождающую матрицу для суммы и пересеченя ядра и образа, если матрица оператора:\n\n$$" ;
tex_matrix(F) ;
cout << "$$\n" ;

Nullim = null_space(Im) ;

cout << "\n%dim_ker=\n%" << dim_ker << endl ;
cout << "\n%dim_im=\n%" << dim_im << endl ;
cout << "\n%dim_its=\n%" << dim_its << endl ;
cout << "\n%dim_sum=\n%" << dim_sum << endl ;
comment_matrix(Ker, "g_ker") ;
comment_matrix(Im, "g_im") ;
comment_matrix(Nullsp, "h_ker") ;
comment_matrix(Nullim, "h_im") ;
comment_matrix(Its,"g_its") ;
comment_matrix(Sum,"g_sum") ;

cerr << "\nОтвет:\n\nРазмерность ядра: " << dim_ker << endl ;
cerr << "\n\nРазмерность образа: " << dim_im << endl ;
cerr << "\n\nРазмерность пересечения: " << dim_its << endl ;
cerr << "\n\nРазмерность суммы: " << dim_sum << endl ;
cerr << "\n\nПорождающая матрица ядра:\n$$\n" ; tex_matrix(Ker,cerr) ; cerr << "$$\n" ; 
cerr << "\n\nПорождающая матрица образа:\n$$\n" ; tex_matrix(Im,cerr) ; cerr << "$$\n" ; 
cerr << "\n\nПроверочная матрица ядра:\n$$\n" ; tex_matrix(Nullsp,cerr) ; cerr << "$$\n" ; 
cerr << "\n\nПроверочная матрица образа:\n$$\n" ; tex_matrix(Nullim,cerr) ; cerr << "$$\n" ; 
cerr << "\n\nПорождающая матрица пересечения:\n$$\n" ; tex_matrix(Its,cerr) ; cerr << "$$\n" ; 
cerr << "\n\nПорождающая матрица суммы:\n$$\n" ; tex_matrix(Sum,cerr) ; cerr << "$$\n" ; 

/*
cout << F ;

myMatrix testKer=nulоl_space(F) ;

if (Ker.concat(testKer).rk() != dim_ker) {cout << "new kernel is BAD ..." << endl ; } 
else {cout << "new kernel is OK  !!!" << test_nod << endl ;} ;
myMatrix testOp = F.transp(), testBig=testOp.concat(Im) ;

if (testBig.rk() != dim_im) 
	{cout <<  (testBig.rk()) << "new image is BAD ..." << dim_im << endl ; }
else {cout << "new image is OK  !!!" << endl ;} ;
*/

 return 0 ;
}
