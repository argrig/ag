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


#include "myvect.h"

int myVector::rnd = 0 ;

//myVector code

	myVector& myVector::operator+= (const myVector& v2) {
		for (size_t i=0; i < size(); i++) {
			(*this)[i] += v2[i] ;
		}
		return *this ;
	}

	myVector& myVector::operator-= (const myVector& v2) {
		for (size_t i=0; i < size(); i++) {
			(*this)[i] -= v2[i] ;
		}
		return *this ;
	}
	
	void myVector::gen_rand (rand_t ibeg, rand_t iend ) {
		for (size_t i=0; i < size(); i++) {
			CUR[i] = (myScalar)(rand()%(iend - ibeg + 1) + ibeg) ;
		}
	};

	void myVector::init_rand () {
		rnd = 1 ;
		ifstream r("/dev/urandom") ;
		rand_t *irand ;
		char* ch ;
		ch = new char[4] ;
		r.get(ch, 4) ;
		irand=(rand_t*)ch ;
		srand (*irand) ;
		delete [] ch ;
		r.close() ;
	}	

void myVector::del(size_t j) {
	for (size_t i=j; i<size()-1; i++) CUR[i] = CUR[i+1] ;
	resize(size()-1) ;
} ;

inline myScalar nod (myScalar a, myScalar b) {
	myScalar q, r ;
	a=abs(a) ; b= abs(b) ;
if (a!=MY_ZERO && b!=MY_ZERO) {
	r = a%b ;
	q = (a-r)/b ;
	while ( r!=MY_ZERO ) {
		a=b ; b=r ;
		r = a%b ; q = (a-r)/b ;
	}
	return b ;
}
else return 0 ;
};

myScalar myVector::nod () {
	myScalar tmp=0 ;
	for (size_t i=0 ; i<CUR.size() ; i++) 
  	  if (CUR[i]!=MY_ZERO) {
  		if ( tmp==MY_ZERO ) tmp=CUR[i] ;
		else tmp = ::nod( tmp, CUR[i] ) ;
	  } ;
	return tmp ;
}

void myVector::socr () {
	myScalar tmp = nod() ;
	if (tmp>MY_ID) 
	for (size_t i=0; i<size(); i++) {
		CUR[i]/=tmp ;
	}
	factor=tmp ;
}

myScalar myVector::abs_max() {
	myScalar mx = abs(CUR[0]) ;
	for (size_t i=1; i<CUR.size(); i++) {
		mx = max ( mx, abs(CUR[i]) ) ;
	}
	return mx ;
};

// end of myVector code

//Operators overloading for myVector

	myVector operator+ (const myVector& v1, const myVector& v2) {
		myVector sum(v1) ;
		for (size_t i=0; i < v1.size(); i++) {
			sum[i] += v2[i] ;
		}
		return sum ;
	}

	myVector operator- (const myVector& v1, const myVector& v2) {
		myVector sum(v1) ;
		for (size_t i=0; i < v1.size(); i++) {
			sum[i] -= v2[i] ;
		}
		return sum ;
	}

	myVector operator* (const myScalar a, const myVector& v) {
		myVector tmp(v) ;
		for (size_t i=0; i < v.size(); i++) {
			tmp[i] *= a ;
		}
		return tmp ;		
	}

	myScalar operator* (const myVector& v1, const myVector& v2) {
	  myScalar prod=MY_ZERO ;
	  for (size_t i=0; i<v1.size(); i++) { prod += (v1[i]*v2[i]) ; }
	  return prod ;
	}
	
	ostream& operator<< (ostream& out, myVector& v) {
		for (size_t i=0; i<v.size(); i++) {	
		  if (i) out << v.cdelim ;
		  out << v[i] ; 
		} 
		return out ;
	};

	istream& operator>> (istream& in, myVector& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	in >> v[i]; } 
		return in ;
	};

myVector operator/ ( const myVector& v, const myScalar a)  {
		myVector tmp(v) ;
		for (size_t i=0; i < v.size(); i++) {
			tmp[i] /= a ;
		}
		return tmp ;		
};


//End of Operators overloading for myVector


// some global functions

size_t wt (size_t w, size_t len) {
  size_t weight=0 ;
  for (size_t i=0; i<len; i++) {
	if ( ((w>>i) & 1) != 0 ) ++weight ;
  }
  return weight ;
} ;

/*
myScalar myrand (size_t rad) {
  myScalar res=0 ;
  while (! res) { res = rand()%(2*rad+1) - rad ; } 
  return res ;
} ;
*/

size_t b2d (char* str) {
  size_t res=0, len=0 ;
  while ( str[len]!=0 ) len++ ;
  for ( size_t i=len; i>0 ; i-- ) {
	if (str[i-1]=='1') res |= 1<<(len-i) ;
  } ;
  return res ;
} ;

char* d2b(size_t num, int n=32) {
	char* bin=new char[n+1];
	for(int i=n-1; i>=0; i--)
		bin[n-1-i]=((num>>i)&1 != 0) ? '1' : '.' ;
	bin[n]='\0';
	return bin;
}



// end some global functions
