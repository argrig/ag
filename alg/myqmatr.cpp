            /************************************************\
            *                                                *
            *  RUSIAN-ARMENIAN (SLAVONIC) STATE UNIVERSITY   *
            *  Author: A. Grigoryants                        *
            *                                                *
            *      ELECTRONIC EXAMINATION SYSTEM             *
            *                                                *
            *       +++++ +   +    + + ++   ++               *
            *       +      + +    +  + + + + +               *
            *       ++      +    +++++ +  +  +               *
            *       +      + +   +   + +     +               *
            *       +++++ +   + +    + +     +               *
            *                                                *
            *                                                *
            *                                                *
            *  Copyright (C) 2003 - 2004                     *
            \************************************************/

#include "myqmatr.h"

  myQMatr::myQMatr (const myMatrix& a) : 
  vector<myQVect> (a.size(), a[0].size()) {
	for (size_t i=0; i<a.size(); i++) {
	  for (size_t j=0; j<a[0].size(); j++) {
		CUR[i][j]=a[i][j]*a[i].idenom/a[i].factor ;
	  }
	}
  }

// Operators overloading fo myQMatr
	myQVect operator* (const myQMatr& A, const myQVect& v) {
		myQVect tmp(A.size()) ;
		for (size_t i=0; i < A.size(); i++) {
			tmp[i] = A[i]*v ;
		}
		return tmp ;
	}

	myQMatr operator* (const myQMatr& A, const myQMatr& B) {
		myQMatr C(A.size(), B[0].size()) ;
		myQVect tmp(B.size()) ;
		for (size_t i=0; i<A.size(); i++) {
			for (size_t j=0; j<B[0].size(); j++) {
				C[i][j] = 0 ;
				for (size_t kk=0; kk<B.size(); kk++) {
					C[i][j] += A[i][kk]*B[kk][j] ;		
				}
			}
		}
		return C ;
	}
	
	myQMatr operator+ (const myQMatr& A, const myQMatr& B) {
		myQMatr C(A) ;
		for (size_t i=0; i<A.size(); i++) {
			C[i] += B[i] ;
		}
		return C ;
	}
	
	myQMatr operator- (const myQMatr& A, const myQMatr& B) {
		myQMatr C(A) ;
		for (size_t i=0; i<A.size(); i++) {
			C[i] -= B[i] ;
		}
		return C ;
	}
	
	
	ostream& operator<< (ostream& out, myQMatr& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	out << v[i] << endl; } 
		return out ;
	};
	
	istream& operator>> (istream& in, myQMatr& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	in >> v[i]; }
		return in ; 
	};	
// End of Operators overloading fo myQMatr

myMatrix::myMatrix (myQMatr Q) {
  this->resize(Q.size()) ;
  for (size_t i=0; i<size(); i++){
	CUR[i] = (myVector)Q[i] ;
  } 
}

myQMatr myQMatr::transp () {
  	size_t k=size() ;
	size_t n=CUR[0].size() ;
	myQMatr T(n,k) ;
	for (size_t i=0; i<k; i++)
		for (size_t j=0; j<n; j++) {
			T[j][i] = CUR[i][j] ;
		}
	return T ;
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

