#include "myqmatr.h"

/*
myMatrix zrot (const myMatrix& a) {
  size_t n=a.size() ;
  size_t m=a[0].size() ;
  myMatrix res(n,m) ;
  for(size_t i=0; i<n; i++) {
	for (size_t j=0; j<m; j++) {
	  res[i][j] = a[n-1-i][m-1-j] ;
	}
  }
  return res ;
} 

myMatrix zcut (const myMatrix& a, size_t istart, size_t jstart,
size_t ioff, size_t joff) {
  myMatrix res(++ioff, ++joff) ;
  for (size_t i=0; i<ioff; i++) {
	for (size_t j=0; j<joff; j++) {
	  res[i][j] = a[istart+i][jstart+j] ;
	}
  }
  return res ;
}

myQMatr qrvs (myMatrix& a) {
  size_t n = a.size() ;
  myMatrix res ; 
  res=a.concat(diag(1,n) ,'|') ;
  res.gaus1() ;
  myMatrix tmp1=zcut(res,0,0,n-1,n-1) ;
  myMatrix tmp2=zcut(res,0,n,n-1,n-1) ;
  tmp1=zrot(tmp1) ; 
  tmp2=zrot(tmp2) ;
  res = tmp1.concat(tmp2, '|') ;
  res.gaus1() ;
  res.socr() ;
  myQMatr res1 = (myQMatr)zrot(zcut(res,0,n,n-1,n-1)) ;
  myQMatr id   = (myQMatr)zrot(zcut(res,0,0,n-1,n-1)) ;
  for (size_t i=0; i<n; i++) {
	for (size_t j=0; j<n; j++) {
	  res1[i][j]/=id[i][i] ;
	}
  }
  return res1 ; 
}
*/

int main() {
  myQScal x ;
  cin >> x ;
  cout << x ;
  exit(0) ;
  myMatrix A = gen_uni(4) ;
  cout << A << endl;
  myQMatr r_A = qrvs(A) ;
  myQMatr prod = r_A*(myQMatr)A ;
  cout << r_A << endl << prod << endl << (((myMatrix)r_A).det1()) << endl;
  prod = (myQMatr)A*r_A ;
  cout << endl << prod ;
}
