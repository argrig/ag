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


#ifndef MYQVECT_H
#define MYQVECT_H

#include "myvect.h"
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

typedef mpq_class myQScal ;
typedef int rand_t ;

/*
#define CUR (*this)
#define MY_ZERO (myQScal)0 
#define MY_ID (myQScal)1 
#define MY_TWO (myQScal)2
#define CF canonicalize()
*/

using namespace std ;

//extern "C" int rand() ;
//extern "C" void srand(unsigned int) ;

class myQVect : public vector<myQScal> {
public:
	char *cdelim ;
	static int rnd ;
	
// Constructors	
	inline void _init() {
		cdelim=" " ;
		if (rnd == 0) {init_rand() ;}
	} ;
	myQVect () : vector<myQScal>() { _init() ; } ;
	myQVect (size_t n) : vector<myQScal>(n) {
	  _init() ;
	} ;
	myQVect (size_t n, myQScal var) : vector<myQScal>(n) {
		_init() ; 
		for (size_t i=0 ; i<n; i++) {CUR[i]=var;} ;
	} ;
	myQVect( const char* ch, size_t n, rand_t interval=9) : vector<myQScal>(n) {
		_init() ;
		if ( ch[0] == 'r' ) gen_rand(-interval, interval) ;		
	} ;
	
	myQVect (myVector v) {
	  for(size_t i=0; i<v.size(); i++) {CUR[i]=v[i] ; }
	}
// End Constructors

//Operators	
	myQVect& operator+= ( const myQVect& ) ; 
	myQVect& operator-= ( const myQVect& ) ;
//End Operators

// Methods
	void init_rand () ;
	void gen_rand (rand_t ibeg=-9, rand_t iend=9 ) ;
	void del(size_t) ;
	myQScal nod () ;
	myQScal abs_max() ;
	 int socr () ;
	 inline int is_null() {myQVect tmp(size(),0) ; return (CUR==tmp) ;} ;
// End Methods
} ; 

// operators overloading
myQVect operator+ (const myQVect&, const myQVect&) ;
myQVect operator- (const myQVect&, const myQVect&) ;
myQVect operator* (const myQScal, const myQVect&)  ;
myQVect operator/ (const myQVect&, const myQScal)  ;
myQScal operator* (const myQVect&, const myQVect&) ;
ostream& operator<< (ostream&, myQVect&) ;
istream& operator>> (istream&, myQVect&) ;
// int operator= (myVector&, myQVect&) ;

// End of myQVect decls

// Some global functions
inline myQScal nod (myQScal, myQScal) ;

/*
inline myQScal abs (myQScal x) {
	return (x<0) ? -x : x ;
}
*/

// End some global functions


#endif //MYQVECT_H
