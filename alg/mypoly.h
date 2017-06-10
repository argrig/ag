#ifndef MYPOLY_H
#define MYPOLY_H
#include "mymatr.h"


class myPolynom : public myVector {
public:

// Constructors
  myPolynom () : myVector () {} ;
  myPolynom (myVector& v) : myVector(v) {} ;
  myPolynom (size_t k) : myVector (k+1) {} ;
  myPolynom (size_t k, myScalar y) : myVector (k+1, y) {} ;
  myPolynom ( const char* ch, size_t k, rand_t interval) : myVector ( ch, k+1, interval=9) {} ;
// End Constructors
  int deg() ;
  myScalar	sen() {return CUR[deg()];} ;
  myScalar	val(myScalar) ;
} ;

  myPolynom  operator+ (const myPolynom&, const myPolynom&) ;
  myPolynom  operator- (const myPolynom&, const myPolynom&) ;
  myPolynom  operator- (const myPolynom&) ;
  myPolynom  operator* (const myPolynom&, const myPolynom&) ;
  myPolynom  operator* (const myScalar, const myPolynom&) ;
  myPolynom* operator/ (const myPolynom&, const myPolynom&) ;
  myPolynom  monom(size_t) ;
  myPolynom  nod(myPolynom, myPolynom) ;

#endif //MYPOLY_H

