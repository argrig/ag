#include "mymatr.h"
#include "mytex.h"

int main() {
  
myScalar dt, dti ;
size_t num ;

myMatrix A(4,5), T(4,5) ;
myVector x(4), b(4) ;

do {
  for (int i=0; i<4; i++) {
	A[i].gen_rand(-7,7) ;
  }
  x.gen_rand(-7,7) ;
  T = A ;
  T.del_col(5) ;
  dt=T.det1() ;
  b = T*x ;
  A.subst_col(b, 4) ;
  num = rand() % 4 ; 
  T.subst_col(b, num) ;
  dti = T.det1() ;
} while ( dt==0 || abs(dt)>9 || b.abs_max() >40 || x[num] != dti/dt) ;

num++ ;
cout << "Hайти неизвестную $x_" << num << "$ используя правило Крамера.\n" ;
tex_equation(A) ;
comment_matrix (A, "eqn") ;
cout << '%' << "d=" << dt << endl ;
cout << '%' << "di=" << dti << endl ;
cout << '%' << "x=" << x[num-1] << endl ;
// cout << '%' << "num=" << num << endl ;
cerr << "Ответ:\n\n" ;
cerr << "$d = " << dt << "$\n\n" ;
cerr << "$d_" << num << " = " << dti << "$\n\n";
cerr << "$x_" << num << " = " << x[num-1] << "$\n\n";

}
