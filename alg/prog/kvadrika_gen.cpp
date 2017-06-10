#include "myqmatr.h"
#include "mytex.h"

#define DIM 3 

int main() {
  myMatrix Q=diag(1,DIM), Q1, C, C_rvs, CT, CT_rvs ;
  myVector d(DIM), d_rvs(DIM), b(DIM,0), b1(DIM) ;
  myScalar c, c1 ;
  size_t type, rk, r_minus ;
  cin >> rk >> r_minus >> type ; 
  if (type == 2) {cin >> c; } ;
  if(rk<3) { Q[2][2]=0; } ;
  if(rk<2) { Q[1][1]=0; } ;
  for(size_t i=0; i<r_minus; i++) { Q[rk-i-1][rk-i-1]=-1; }
  if (type==1 && rk==2) {b[2]=1 ;} ;
  if (type==1 && rk==1) {b[1]=1 ;} ;

  do {
	  C=gen_uni(3) ;	C_rvs = qrvs(C) ;
    CT=C.transp();	CT_rvs=C_rvs.transp() ;
	  Q1 = CT_rvs*Q*C_rvs ;
    d.gen_rand(-7,7) ;
    d_rvs = (myScalar)(-1)*(C_rvs*d) ;
    b1 = (myScalar)2*((CT_rvs*Q)*d_rvs) + CT_rvs*b ;
    c1 = d_rvs*(Q*d_rvs) + b*d_rvs + c ;
  } while (Q1.abs_max()>50 || Q1.has_null() || b1.abs_max()>50 || c1>50);
  
  cout	<< "Исследовать поверхность, приведя ее к каноническому виду "
		    << "аффинным преобразованием координат:\n$$\n" ;
  tex_surf(Q1, b1, c1, cout) ;
  cout << "\n$$\n"; cout << "\n%c=\n%" << c1 << endl ;
  comment_matrix (Q, "Q_cn") ;
  comment_matrix (Q1, "Q") ;
  comment_matrix (C,"C") ;
  myMatrix D(1,DIM) ; D[0] = d ;
  comment_matrix (D,"d") ;
  myMatrix B1(1,DIM) ; B1[0] = b1 ;
  comment_matrix (B1,"b") ;

  cerr << "Вектор сдвига:\n" ;
  cerr << "$$\n\\vec{b}~=~" ; tex_vect(d,cerr) ; cerr << "\n$$\n\n" ;
  cerr << "Матрица перехода к каноническому базису:\n" ;
  cerr << "$$\n" ; tex_matrix(C,cerr) ; cerr << "$$\n" ;

}
