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

#ifndef MYMATR_H
#define MYMATR_H
#include "myvect.h"
//#include "mytempl.h"

//template <class Scal, class Vect> class Matr ;
//template class Matr<myScalar, myVector> ;

class myQMatr ;
//myMatrix decls

class myMatrix : public vector<myVector> {
public:
cnt_vect_t main_vect ;

// Constructors
	myMatrix () : vector<myVector>() {} ;
//	myMatrix (Matr<myScalar, myVector>) ;
	myMatrix (size_t k, size_t n) : vector<myVector>(k) {
		main_vect.resize(0);
		for (size_t i=0; i<k; i++) { (*this)[i].resize(n) ;}
	} ;
	myMatrix (size_t k, size_t n, myScalar val) : vector<myVector>(k) {
		main_vect.resize(0) ;
		myVector zero(n, 0) ; 
		for (size_t i=0; i<k; i++) { 
		  CUR[i] = zero ;
		  if(i<n) CUR[i][i] = val ;
		}
	} ;
	myMatrix (myVector v) : vector<myVector>(1) { CUR[0] = v ; }
	
	myMatrix (myQMatr) ;
	
	myMatrix ( char* ch, size_t k, size_t n,
					rand_t ibeg=-9, rand_t iend=9 ) : vector<myVector>(k) {
		main_vect.resize(0);
		for (size_t i=0; i<k; i++) { 
		
		 	(*this)[i].resize(n) ;
			(*this)[i].gen_rand(ibeg, iend) ;
		}
	} ;
// End Constructors

	friend myVector operator* (const myMatrix&, const myVector&) ;
	friend ostream& operator<< (ostream&, myMatrix&) ;

// METHODS
	void gen_rand ( rand_t ibeg=-9, rand_t iend=9 ) {
		for (size_t i=0; i<size(); i++) { 
			CUR[i].gen_rand(ibeg, iend) ;
		}
	} ;
	void delim (char* delim="\t") {
	  size_t k = size() ;
	  for (size_t i=0; i<k; i++) {
		CUR[i].cdelim=delim ;
	  }    
	} ; 
	
	size_t* gaus_step(size_t*) ;
	size_t* gaus_step1(size_t*) ;
	myVector gaus (const char* style="", size_t* ij=0) ;
	cnt_vect_t gaus1 (const char* style="", size_t* ij=0) ;
	myScalar det () ;
	myScalar det1 () ;
	size_t rk () ;
	myScalar abs_max () ;
	int subst_col (myVector, size_t) ;
	inline int has_null_row() {
		size_t i=0 ;
		while (i<size() && !CUR[i].is_null() ) i++ ;
		return (i==size()) ? 0 : ++i ;
	};
	
	int has_null() {
		myMatrix B=transp() ;
		return ( has_null_row() || B.has_null_row() ) ;
	};

	int has_null_col() {
		myMatrix B=transp() ;
		return ( B.has_null_row() ) ;
	};

	
	void del_row (size_t) ;
	void del_col (size_t) ;

//	void gen_step_matr(size_t k=4, size_t n=7, const size_t dep_mask=102, // binary 11..11.
//			myScalar d1=-5, myScalar d2=5, size_t prior=0) ;
	void gen_step(const size_t dep_mask=102, // binary 11..11.
			rand_t d1=-5, rand_t d2=5) ;
	myMatrix hash(size_t rad=3, size_t imax=9) ;
	myMatrix concat(myMatrix, char type='-' )	;
//	void gen_matr(size_t k, size_t n, 
//					myScalar d1=0, myScalar d2=0, size_t dep_mask=0, size_t prior=0) ;
	void socr() { for (size_t i=0; i<size(); i++) CUR[i].socr() ;} ;	
	myMatrix rvs () ;
	myMatrix transp () ;
//END METHODS 
	
} ;

//operators overloading
	myVector operator* (const myMatrix&, const myVector&) ;
	myMatrix operator* (const myMatrix&, const myMatrix&) ;
	myMatrix operator+ (const myMatrix&, const myMatrix&) ;
	myMatrix operator- (const myMatrix&, const myMatrix&) ;
	ostream& operator<< (ostream&, myMatrix&) ;
	istream& operator>> (istream&, myMatrix&) ;
// End of myMatrix decls

myMatrix diag(const myScalar, const size_t) ;
int my_in (const myScalar, const myVector) ;

myMatrix gen_uni (size_t, rand_t det=1, rand_t sign=0) ;
myMatrix zrot (const myMatrix& a) ;
myMatrix zcut (const myMatrix&, size_t, size_t, size_t, size_t) ;

#endif // MYMATR_H
