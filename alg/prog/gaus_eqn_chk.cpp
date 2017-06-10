#include "mymatr.h"
#include "mytex.h"


int main () {
  myVector empty(0) ;
  size_t k=0, n=0 ;
  int usr_joint ;  

  cin >> k >> n ;
  myMatrix A (k, n), B(k, n) ;
  cin >> A >> B ;
  cin >> usr_joint ;
//  cout << k << n << A << A.rk(); exit(0) ;
  
  myMatrix C = A.concat(B) ;
  if ( C.rk() != A.rk() || B.rk() != A.rk() ) {cout << 1; exit(1) ; }// wrong rank
  
  for (size_t i=0; i<k; i++)
  for (size_t j=0; A[i][j]==0 && j<n; j++)
	  if ( B[i][j]!=0 ) { cout << 2; exit(2) ; }  // wrong step style
  A.gaus1() ;
  int rk = A.main_vect.size() ;
  int joint = -100 ;
  if (A.main_vect[rk-1] == n-1) {joint = 3; } 
  else if (rk == n-1) {joint = 1; }
  else joint = 2 ;
  if (joint != usr_joint) { cout << 3; exit (3) ; } ;
  cout << 0 ; return 0 ;
}
