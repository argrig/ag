#include "mypoly.h"  
#include "mytex.h"

int main () {

myVector empty(0) ;
size_t deg_nod = rand()%3 ;
size_t deg_p = 5-deg_nod ;
size_t deg_q = 4-deg_nod ;

myPolynom _nod (deg_nod, 0) ;
_nod.gen_rand (-3, 3) ;
myPolynom p (deg_p, 0) ;
p.gen_rand (-3, 3) ;
myPolynom q (deg_q, 0) ;
q.gen_rand (-3, 3) ;

p[deg_p] = myrand(2) ;
q[deg_q] = 1 ;
_nod[deg_nod] = 1 ;

p = p*_nod ;
q = q*_nod ;

myPolynom nd = nod (p, q) ;

bool fig = deg_nod==nd.deg() ;
  if (fig) { 
	for (int i; i<=deg_nod; i++) 
	  fig = fig && (_nod[i] == nd[i]) ; 
  } ; 


if (fig) {
cout	<< "Найти наибольший общий делитель многочленов, имейющий "
	    << "целые коэффициенты и минимальный положительный старший коэффициент:\n" ;
cout	<< "\n$p(x)~=~" ; tex_polynom(p, 0) ; cout << "$\n" ;
cout	<< "\n$q(x)~=~" ; tex_polynom(q, 0) ; cout << "$\n" ;

myVector v=_nod ;
cout	<< "%nod=\n%" << v ;

cerr	<< "Ответ:\n\nНОД$(p,~q)~=~" ; tex_polynom(_nod, 0, cerr) ;
cerr	<< "$\n" ; 
}
else exit(1) ;

}
