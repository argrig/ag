#include "mymatr.h"
#include "mytex.h"


int main () {

  size_t k=0, n=0 ;
  int usr_joint ;
  int usr_fund ;

  cin >> k >> n ;

  myVector usr_sol(n-1) ;
  myMatrix A (k, n), B(k, n) ;
  cin >> A >> B ;
  
  int rk_A = A.rk() ;
  int rk_B = B.rk() ;
  
  int fund = n-1-rk_A ; 
  myMatrix F(fund, n-1) ;
  cin >> F ;
  
  myVector b(k) ;
  for (int i=0; i<k; i++) {
	b[i] = A[i][n-1] ;
  }
  
  cin >> usr_sol ;      

  
  myMatrix C = A.concat(B) ;
  if ( C.rk() != A.rk() || B.rk() != A.rk() ) {cout << 1; exit(1) ; }// wrong rank
  


  for (size_t i=0; i<k; i++)
  for (size_t j=0; A[i][j]==0 && j<n; j++)
	  if ( B[i][j]!=0 ) { cout << 2; exit(2) ; }  // wrong step style
  

  myMatrix AA = A ; AA.del_col(n-1) ;
  for (int i=0; i<fund; i++) {
	if ( ! (AA*F[i]).is_null() ) {  //wrond fund system
	  cout << 5 ; exit (5) ;
	}
  }
    
  A.del_col(n-1) ;
  if (A*usr_sol != b) {cout << 6; exit (6); } //wrong solution
  
  cout << 10 ; 
  return 10 ;
}
