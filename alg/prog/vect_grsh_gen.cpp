#include "mymatr.h"
#include "mytex.h"
#include "myqvect.h"

int main () {
  const size_t num  = 4 ;
  const size_t size = 4 ;
  
  myMatrix A(num, size), BB(num, size);
  myQVect B[num] ;
  for (size_t i=0; i<num; i++) {B[i].resize(size) ;} ;
  
  do {
	A.gen_rand(-5, 5) ;
  } while( A.rk()<min(num,size) ) ;
    
  for (size_t i=0; i<num; i++) {
	for (size_t k=0; k<size; k++) {B[i][k]=A[i][k] ; }
	myQVect tmp=B[i] ;
	for(size_t j=0; j<i; j++) {
	  myQScal coef = (tmp*B[j])/(B[j]*B[j]) ;
	  B[i] = B[i] - coef*(myQVect)B[j] ; 
	}
  }
  
  for (size_t i=0; i<num; i++) {
	myScalar lcm=1, gcd=B[i][0].get_num();
	for (size_t k=0; k<size; k++) {
	  mpz_lcm(lcm.get_mpz_t(), lcm.get_mpz_t(), B[i][k].get_den().get_mpz_t());
	  mpz_gcd(gcd.get_mpz_t(), gcd.get_mpz_t(), B[i][k].get_num().get_mpz_t());
	}
	B[i]=(myQScal)lcm*B[i]/gcd ;
  }
  
  cout	<< "С помощью процесса ортогонализации Грамма-Шмидта ортогонализировать "
		<< "следующую систему векторов (получить целочисленную ортогональную систему):\n\n"
		<< "\n$$\n\\begin{array}{l}\n" ;		
  		for (int i=0; i<num; i++) {
		  cout << "\\vec{e}_" << i+1 <<" = (";
		  for (int j=0; j<size; j++) {
			if(j) cout << ";" ;
			cout << "~" << A[i][j] ;
		  }
		  cout << "~)\\\\\n" ;
		}		
  cout	<< "\\end{array}\n$$\n" ;
  
  comment_matrix (A,"A") ;
  
  for(size_t i=0; i<num; i++) {
	for (size_t j=0; j<size; j++) {
	  BB[i][j]=B[i][j].get_num() ;
	}
  }
  comment_matrix (BB,"B") ;
  cerr << "Ответ:\n\n Ортогонализированная система:\n"
		<< "$$\n\\begin{array}{l}\n" ;		
  		for (int i=0; i<num; i++) {
		  cerr << "\\vec{f}_" << i+1 <<" = (";
		  for (int j=0; j<size; j++) {
			if(j) cerr << ";" ;
			cerr << "~" << B[i][j] ;
		  }
		  cerr << "~)\\\\\n" ;
		}		
  cerr	<< "\\end{array}\n$$\n" ;

}

