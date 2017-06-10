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


#include "myqvect.h"

int myQVect::rnd = 0 ;

myVector::myVector (myQVect& v) {
  _init() ;
  size_t sz=v.size() ;
  this->resize(sz) ;
//  myScalar tnum=1 ;
  myQScal tden=1 ;
  for (size_t i=0; i<sz; i++) {
	v[i].CF ;
	tden*=v[i].get_den() ;
	CUR[i] = v[i].get_num() ;
	for (size_t j=i+1; j<sz; j++) {
	  v[j]*= v[i].get_den() ;
	}
  }
  socr() ;
  tden=(myQScal)factor/tden ;
  tden.CF ;
  factor = tden.get_num() ;
  idenom = tden.get_den() ;
} 


//myQVect code
	myQVect& myQVect::operator+= (const myQVect& v2) {
		for (size_t i=0; i < size(); i++) {
			(*this)[i] += v2[i] ;
		}
		return *this ;
	}

	myQVect& myQVect::operator-= (const myQVect& v2) {
		for (size_t i=0; i < size(); i++) {
			(*this)[i] -= v2[i] ;
		}
		return *this ;
	}
	
	void myQVect::gen_rand (rand_t ibeg, rand_t iend ) {
		for (size_t i=0; i < size(); i++) {
			CUR[i] = (myQScal)(rand()%(iend - ibeg + 1) + ibeg) ;
		}
	};

	void myQVect::init_rand () {
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

void myQVect::del(size_t j) {
	for (size_t i=j; i<size()-1; i++) CUR[i] = CUR[i+1] ;
	resize(size()-1) ;
} ;

/*
myQScal nod (myQScal a, myQScal b) {
	myQScal q, r ;
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

myQScal myQVect::nod () {
	myQScal tmp=0 ;
	for (int i=0 ; i<CUR.size() ; i++) 
  	  if (CUR[i]!=MY_ZERO) {
  		if ( tmp==MY_ZERO ) tmp=CUR[i] ;
		else tmp = ::nod( tmp, CUR[i] ) ;
	  } ;
	return tmp ;
}

int myQVect::socr () {
	myQScal tmp = nod() ;
	if (tmp>MY_ID) 
	for (size_t i=0; i<size(); i++) {
		CUR[i]/=tmp ;
		factor*=tmp ;
	}
}
*/

myQScal myQVect::abs_max() {
	myQScal mx = abs(CUR[0]) ;
	for (size_t i=1; i<CUR.size(); i++) {
		mx = max ( mx, abs(CUR[i]) ) ;
	}
	return mx ;
};

// end of myQVect code

//Operators overloading for myQVect

	myQVect operator+ (const myQVect& v1, const myQVect& v2) {
		myQVect sum(v1) ;
		for (size_t i=0; i < v1.size(); i++) {
			sum[i] += v2[i] ;
		}
		return sum ;
	}

	myQVect operator- (const myQVect& v1, const myQVect& v2) {
		myQVect sum(v1) ;
		for (size_t i=0; i < v1.size(); i++) {
			sum[i] -= v2[i] ;
		}
		return sum ;
	}

	myQVect operator* (const myQScal a, const myQVect& v) {
		myQVect tmp(v) ;
		for (size_t i=0; i < v.size(); i++) {
			tmp[i] *= a ;
		}
		return tmp ;		
	}

	myQScal operator* (const myQVect& v1, const myQVect& v2) {
	  myQScal prod=MY_ZERO ;
	  for (size_t i=0; i<v1.size(); i++) { prod += (v1[i]*v2[i]) ; }
	  return prod ;
	}
	
	ostream& operator<< (ostream& out, myQVect& v) {
		for (size_t i=0; i<v.size(); i++) {	
		  if (i) out << v.cdelim ;
		  out << v[i] ; 
		} 
		return out ;
	};

	istream& operator>> (istream& in, myQVect& v) {
		for (size_t i=0; i<v.size(); i++) 
			{	in >> v[i]; } 
		return in ;
	};

myQVect operator/ ( const myQVect& v, const myQScal a)  {
		myQVect tmp(v) ;
		for (size_t i=0; i < v.size(); i++) {
			tmp[i] /= a ;
		}
		return tmp ;		
};


//End of Operators overloading for myQVect


/*
// some global functions
size_t wt (size_t w, size_t len) {
  size_t weight=0 ;
  for (size_t i=0; i<len; i++) {
	if ( ((w>>i) & 1) != 0 ) ++weight ;
  }
  return weight ;
} ;

myQScal myrand (size_t rad) {
  myQScal res=0 ;
  while (! res) { res = rand()%(2*rad+1) - rad ; } 
  return res ;
} ;

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
*/

