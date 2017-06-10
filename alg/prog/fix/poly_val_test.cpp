#include <mymatr.h>
#include <mytex.h>

int main() {
  size_t n ;
  myScalar a ;
  cin >> n ;
  myVector v(n+1) ;
  cin >> v >> a ;
  myPolynom p(v) ;
  tex_polynom(p) ;
  myScalar x=p.val(a) ;
  cout << endl << x ;
  return 0 ;
}

