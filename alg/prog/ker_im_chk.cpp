#include "mymatr.h"


int main () {
// parameters
size_t dim, DIM ; 
cin >> dim >> DIM ;

myMatrix  ans(dim,DIM,0), usr(dim,DIM,0);
cin >>  ans >> usr ;

if ( usr.rk() == dim && (ans.concat(usr)).rk() == dim ) {
	cout << "ok" ;
  return 1 ;
}
else{
  return 0 ;
}
}
