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


#ifndef MYVECT_H
#define MYVECT_H


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

typedef mpz_class myScalar ;
typedef int rand_t ;

#define CUR (*this)
#define MY_ZERO (myScalar)0 
#define MY_ID (myScalar)1 
#define MY_TWO (myScalar)2
#define CF canonicalize()

using namespace std ;

// extern "C" int rand() ;
// extern "C" void srand(unsigned int) ;


class cnt_vect_t : public vector<size_t> {
public:	
	cnt_vect_t () : vector<size_t>() {} ;
	cnt_vect_t (size_t n) : vector<size_t>(n) {} ;
	cnt_vect_t (size_t n, size_t var) : vector<size_t>(n) {
		for (size_t i=0 ; i<n; i++) {CUR[i]=var;} ;
	} ;
} ;


//typedef long long myScalar ;
//typedef mpq_class myScalar ;
//typedef int rand_t ;
// typedef long myScalar ;

class myQVect ;
class myVector : public vector<myScalar> {
public:
//	float fdenom  ;
//	signed long long idenom ;
	myScalar idenom ;
	myScalar factor ;
	char *cdelim ;
//	myScalar idenom ;
	static int rnd ;
	
// Constructors	
	inline void _init() {
		idenom=MY_ID ;
		factor=MY_ID ;
		cdelim=" " ;
		if (rnd == 0) {init_rand() ;}
	} ;
	myVector () : vector<myScalar>() { _init() ; } ;
	myVector (size_t n) : vector<myScalar>(n) {
	  _init() ;
	} ;
	myVector (size_t n, myScalar var) : vector<myScalar>(n) {
		_init() ; 
		for (size_t i=0 ; i<n; i++) {CUR[i]=var;} ;
	} ;
	myVector (const char* ch, size_t n, rand_t interval=9) : vector<myScalar>(n) {
		_init() ;
		if ( ch[0] == 'r' ) gen_rand(-interval, interval) ;		
	};
	myVector (myQVect&) ;
// End Constructors

//Operators	
	myVector& operator+= ( const myVector& ) ; 
	myVector& operator-= ( const myVector& ) ;
//End Operators

// Methods
	void init_rand () ;
	void gen_rand (rand_t ibeg=-9, rand_t iend=9 ) ;
	void del(size_t) ;
	myScalar nod () ;
	myScalar abs_max() ;
	void socr () ;
	 inline int is_null() {myVector tmp(size(),0) ; return (CUR==tmp) ;} ;
// End Methods
} ; 

// operators overloading
myVector operator+ (const myVector&, const myVector&) ;
myVector operator- (const myVector&, const myVector&) ;
myVector operator* (const myScalar, const myVector&)  ;
myVector operator/ (const myVector&, const myScalar)  ;
myScalar operator* (const myVector&, const myVector&) ;
ostream& operator<< (ostream&, myVector&) ;
istream& operator>> (istream&, myVector&) ;

// End of myVector decls

// Some global functions
myScalar nod (myScalar, myScalar) ;

/*
inline myScalar abs (myScalar x) {
	return (x<0) ? -x : x ;
}
*/

inline myScalar min (myScalar x, myScalar y) {
	return (x<y) ? x : y ;
} ;

inline myScalar max (myScalar x, myScalar y) {
	return (x<y) ? y : x ;
} ;

size_t wt (size_t w, size_t len=32) ;


inline myScalar myrand (size_t rad) {
  rand_t res=0 ;
  while (res==0) { res = rand()%(2*rad+1) - rad ; } 
  return res ;
} ;



inline int myrand (rand_t d1, rand_t d2) {
  return rand()%(d2 - d1 + 1) + d1 ;
}

size_t b2d (char* str) ;

char* d2b(size_t, int n) ;

// End some global functions


#endif //MYVECT_H
