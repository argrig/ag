#include "myqmatr.h"
#include "mytex.h"

int main() {
  size_t dim=3, r, r_minus, usr_r=0, usr_r_minus=0 ; //SUBJECT TO CHANGE
  
  myQMatr Q_cn(dim,dim), C(dim,dim);
  myQMatr Q1(dim,dim) ;
  cin >> Q_cn >> C >> Q1 >> r >> r_minus  ;
//  cout << Q_cn << C << Q1 << r << r_minus ;
  for(size_t i=0; i<dim; i++) {
	for(size_t j=0; j<dim; j++) {
	  if(i==j) {
		if (Q_cn[i][j]==1) {usr_r++;}
		else if (Q_cn[i][j]==-1) {usr_r_minus++; usr_r++;}
		else if (Q_cn[i][j]==0) {}
		else {cout << 3 ; exit(3);} //неверная матрица канонического вида
	  }
	  else if (Q_cn[i][j]!=0) {cout << 3 ; exit(3);} //неверная матрица канонического вида
	}
  }
  if (r!=usr_r || r_minus!=usr_r_minus) 
	{cout << 3 ; exit(3);} //неверная матрица канонического вида
  myQMatr CT=C.transp() ;
  myQMatr Q_usr = CT*Q1*C ;
  for (size_t i=0; i<dim; i++) {
	for (size_t j=0; j<dim; j++) {
	  if (abs(Q_usr[i][j]-Q_cn[i][j])>0.001) {cout << 4 ; exit(4);} //неверное преобразование
	}
  }
  cout << 5 ; exit(5); // все нормально
}
