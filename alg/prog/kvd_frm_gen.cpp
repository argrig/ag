#include "myqmatr.h"
#include "mytex.h"

int main() {
  myMatrix Q=diag(1,3), Q1, C, C_rvs, CT, CT_rvs ;
  size_t rk = rand()%2 + 2;
  size_t r_minus = rand()%(rk+1) ;
  if(rk==2) { Q[2][2]=0; } 
  for(size_t i=0; i<r_minus; i++) { Q[rk-i-1][rk-i-1]=-1; }
  do {
	C=gen_uni(3) ;	C_rvs = qrvs(C) ;
    CT=C.transp();	CT_rvs=C_rvs.transp() ;
	Q1 = CT_rvs*Q*C_rvs ;
  } while (Q1.abs_max()>50 || Q1.has_null());
  
  cout	<< "Исследовать квадратичную форму, вычислив "
		<< "ранг, сигнатуру, канонический вид и канонический базис:\n$$\n" ;
  tex_kv_frm(Q1) ;
  cout << "\n$$\n\n%rk=\n%" << rk << "\n\n%r_minus=\n%" << r_minus << endl ;
  comment_matrix (Q, "Q_cn") ;
  comment_matrix (Q1, "Q1") ;
  comment_matrix (C,"C") ;
  
  cerr 	<< "Ответ:\n\nМатрица исходной формы:\n$$\n" ;
		tex_matrix(Q1, cerr) ;
  cerr	<< "$$\n\nРанг формы: " << rk << "\n\nСигнатура: ("
		<< rk-r_minus << ";~" << r_minus << ")\n\nКанонический вид:\n$\n" ;
		tex_kv_frm(Q,cerr) ;
  cerr	<< "$\n\nМатрица перехода к каноническому базису:\n\n$$\n" ;
		tex_matrix (C, cerr) ;
  cerr	<< "$$\n\nМатрица канонического вида:\n$$\n" ;
		tex_matrix(Q,cerr) ;
  cerr	<< "$$\n" ;
  
}
