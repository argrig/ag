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

#ifndef MYQMATR_H
#define MYQMATR_H
#include "mymatr.h"
#include "myqvect.h"

//myQMatr decls
class myQMatr : public vector<myQVect> {
public:
cnt_vect_t main_vect ;

// Constructors
	myQMatr () : vector<myQVect>() {} ;
	myQMatr (const myMatrix& a)  ;
	myQMatr (size_t k, size_t n) : vector<myQVect>(k) {
		main_vect.resize(0);
		for (size_t i=0; i<k; i++) { (*this)[i].resize(n) ;}
	} ;
	myQMatr (myQVect v) : vector<myQVect>(1) { CUR[0] = v ; }
	myQMatr transp () ;
	
// End Constructors

	friend myQVect operator* (const myQMatr&, const myQVect&) ;
	friend ostream& operator<< (ostream&, myQMatr&) ;

} ;

//operators overloading
	myQVect operator* (const myQMatr&, const myQVect&) ;
	myQMatr operator* (const myQMatr&, const myQMatr&) ;
	myQMatr operator+ (const myQMatr&, const myQMatr&) ;
	myQMatr operator- (const myQMatr&, const myQMatr&) ;
	ostream& operator<< (ostream&, myQMatr&) ;
	istream& operator>> (istream&, myQMatr&) ;
// End of myQMatr decls

myQMatr qrvs (myMatrix&) ;

#endif // MQYMATR_H
