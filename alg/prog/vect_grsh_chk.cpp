#include "mymatr.h"
#include "mytex.h"

int main () {
  const size_t k=4, n=4 ;  

  myMatrix A (k, n), B(k, n) ;
  cin >> A >> B ;
  
  if(B.rk()<k) {cout<< 10; return 10;} // linear dependent
  for(size_t i=0; i<k; i++) {
	myMatrix AA=A, BB=B ;
	AA.resize(i+1) ;
	BB.resize(i+1) ;
	myMatrix C = AA.concat(BB) ;
	if(C.rk()>i+1) {cout << (i+1); return (i+1) ;} ; //wrong vector
  }
  
  for(size_t i=0; i<k; i++) {
    for(size_t j=i+1; j<k; j++) {
	  if(B[i]*B[j] != 0) {cout << (10+j+1) ; return (10+j+1) ;} // not orthogonal
	}
  }
  cout << 20 ;
  return 20 ; //ok!
}
