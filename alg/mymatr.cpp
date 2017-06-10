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

#include "mymatr.h"

//myMatrix code

/*
myMatrix::myMatrix (Matr<myScalar, myVector> b) {
  matr_eq(this, b) ;
} ;
*/


size_t* myMatrix::gaus_step1(size_t* ij=0) {

#define	I 	ij[0]
#define J	ij[1]
	if (ij==0) {
		ij = new size_t[2] ;
		I=0; J=0;
	}
	size_t i=I ;
	while( i<size() ) {	
		while (i<size()) { 
		  if ( CUR[i][J] == MY_ZERO ) {i++ ;} 
		  else break ;
		};
		if (i == size()) J++ ;
		else {
			main_vect.push_back(J) ;
			if(i != I) {
				myVector tmp(CUR[i]) ;
				CUR[i]=CUR[I] ;
				CUR[I]=tmp ;
				CUR[0].idenom=-CUR[0].idenom ;
			}
			for (i=I+1; i<size(); i++) {
				myScalar tnod = nod(CUR[I][J], CUR[i][J]) ;
					myVector tvec = CUR[I][J]*CUR[i] - CUR[i][J]*CUR[I] ;
						CUR[i] = (tnod!=MY_ZERO) ? tvec/tnod : tvec ;
						CUR[0].idenom*= (tnod!=MY_ZERO) ? CUR[I][J]/tnod : CUR[I][J] ;
			}
			I++; J++;
		}			
	}
	return ij ;
} 


cnt_vect_t myMatrix::gaus1 (const char* style, size_t* ij) {
//	myVector tmp(0) ;
	main_vect.resize(0) ;
	do {
		ij = gaus_step1(ij) ;
		if (style[0]=='v') cout << CUR << endl  ;
	} while ( I<size() && J<CUR[0].size() ) ;
	return main_vect ;
};

size_t myMatrix::rk () {
  myMatrix tmp=CUR ;
  tmp.gaus1 () ;
  return tmp.main_vect.size() ;
}

/*
myScalar myMatrix::det() {
	myMatrix tmp(CUR) ;
	myScalar dt=1 ;
	tmp.gaus1() ;
	for (size_t i=0; i<size(); i++) dt*=tmp[i][i]*tmp[i].factor ;
	dt/=tmp[0].idenom ;
}
*/

myScalar myMatrix::det1() {
	myMatrix tmp(CUR) ;
	myScalar dt=1 ;
//	myScalar dt=1 ;
	tmp.gaus1() ;
	for (size_t i=0; i<size(); i++) dt*=tmp[i][i]*tmp[i].factor ;
	// cerr << dt << '\t' << tmp[0].idenom << endl;
	dt/=tmp[0].idenom ;
	
// my extra change : comment
//	socr() ;
// end
	return dt ;
}

void myMatrix::del_row(size_t j) {
	for (size_t i=j; i<size()-1; i++) CUR[i] = CUR[i+1] ;
	resize(size()-1) ;
} ;

void myMatrix::del_col(size_t j) {
	for (size_t i=0; i<size(); i++) CUR[i].del(j) ;
} ;


int myMatrix::subst_col (myVector v, size_t pos) {
	if (v.size() == size()) {
		for (size_t i=0; i<size(); i++) CUR[i][pos] = v[i] ;
		return 1 ;
	}
	else return 0 ;
}

myMatrix myMatrix::rvs() {
	myScalar det = det1() ;
	
	if (det!=MY_ZERO) {
		myMatrix B(CUR), tmp(CUR) ;
		for (size_t i=0; i<size(); i++) {
			for (size_t j=0; j<size(); j++) {
				tmp.del_row(i) ; tmp.del_col(j) ;
				myScalar dd=tmp.det1() ;
				B[j][i] =  ((i+j)%2) ? (myScalar)-dd : dd  ;
				tmp = CUR ;
			}
		}
		B[0].idenom=det ;
		return B ;
	}
	else { 
		cerr << "can't be reversed ..... det = 0" ;
		return CUR ;
	}
}

myMatrix myMatrix::transp () {
	size_t k=size() ;
	size_t n=CUR[0].size() ;
	myMatrix T(n,k) ;
	for (size_t i=0; i<k; i++)
		for (size_t j=0; j<n; j++) {
			T[j][i] = CUR[i][j] ;
		}
	return T ;
}

myScalar myMatrix::abs_max() {
	myVector mx(size()) ;
	for (size_t i=0; i<size(); i++) {
		mx[i] = CUR[i].abs_max() ;
	}
	return mx.abs_max() ;
}


myMatrix myMatrix::concat(myMatrix B , char type) {
  myMatrix res=CUR ;
  size_t k=size() ;
  if (type=='-') {
	res.resize(k+B.size()) ;
    for (size_t i=k; i<res.size(); i++) {
	  res[i] = B[i-k] ;
	}
  }
  if(type=='|') {
	myMatrix tmp1=transp() ;
	myMatrix tmp2=B.transp() ;
	res = (tmp1.concat(tmp2,'-')).transp() ;
  }
  return res ;
}

myMatrix myMatrix::hash(size_t rad, size_t imax) {
  myMatrix tmp ;
  bool cond ;
  do {
	tmp=CUR ;
	for (size_t i=0 ; i<size(); i++) {
	  for ( size_t j=0 ; j<size() ; j++ ) {
		if ( i != j )
		  tmp[i]+=myrand(rad)*tmp[j] ;
	  }
	}
	cond = (CUR.has_null_col()) ?
	  (tmp.abs_max() > (myScalar)imax) || tmp.has_null_row() :
	  (tmp.abs_max() > (myScalar)imax) || tmp.has_null() ;
  } while (cond) ;
  return tmp ;
}

void myMatrix::gen_step(const size_t dep_mask, // binary 11..11.
		rand_t d1, rand_t d2) {
	main_vect.resize(0);
	size_t k = CUR.size() ;
	size_t n = CUR[0].size() ;
	const size_t rad=3 ;
	
	do {	
  	  for (size_t i=0; i<k; i++)
  		for (size_t j=0; j<n; j++) CUR[i][j] = 0 ;
	  for (size_t i=0, cnt=0; i<k && cnt<n; i++, cnt++) { 
		for ( ; (!((dep_mask>>(n-cnt-1)) & 1)) && cnt<n ; cnt++) ;
		if (cnt==n) break ;
		CUR[i][cnt]=myrand(rad) ;
		for (size_t j=cnt+1; j<n; j++) { 
		  CUR[i][j]= myrand(d1, d2); 
		}
	  }
//	  socr() ;
	} while ( has_null_col () ) ;
		
} ;


//End of myMatrix code

// Operators overloading fo myMatrix
	myVector operator* (const myMatrix& A, const myVector& v) {
		myVector tmp(A.size()) ;
		for (size_t i=0; i < A.size(); i++) {
			tmp[i] = A[i]*v ;
		}
		return tmp ;
	}

	myMatrix operator* (const myMatrix& A, const myMatrix& B) {
		myMatrix C(A.size(), B[0].size()) ;
		myVector tmp(B.size()) ;
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
	
	myMatrix operator+ (const myMatrix& A, const myMatrix& B) {
		myMatrix C(A) ;
		for (size_t i=0; i<A.size(); i++) {
			C[i] += B[i] ;
		}
		return C ;
	}
	
	myMatrix operator- (const myMatrix& A, const myMatrix& B) {
		myMatrix C(A) ;
		for (size_t i=0; i<A.size(); i++) {
			C[i] -= B[i] ;
		}
		return C ;
	}
	
	
	ostream& operator<< (ostream& out, myMatrix& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	out << v[i] << endl; } 
		return out ;
	};
	
	istream& operator>> (istream& in, myMatrix& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	in >> v[i]; }
		return in ; 
	};	
// End of Operators overloading fo myMatrix

myMatrix diag( const myScalar val, const size_t sz) {
  myMatrix tmp(sz, sz) ;
  myVector zero(sz, 0) ;
  for (int i=0 ; i<sz; i++) {
	tmp[i] = zero ;
	tmp[i][i] = val ;
  }
  return tmp ;
}

int my_in (const myScalar x, const myVector v) {
  for (int i=0; i<v.size(); i++) {
	if (x==v[i]) {
	  return 1 ;
	}
  }
  return 0 ;
}

myMatrix gen_uni (size_t n, rand_t det, rand_t sign) {
  myMatrix res("rand",n,n,-3,3) ;
  if (sign==0 && rand()%2) {det=-det;}
  for (size_t i=0; i<n; i++){
	for (size_t j=0; j<i; j++) { 
	  res[i][j]=MY_ZERO ; 
	}
	res[i][i]=(myScalar)1 ;
  }
  res[n-1][n-1]=det ;
  res=res.hash() ;
  res=res.transp() ;
  res=res.hash(2,14) ;
  return res ;
}

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
