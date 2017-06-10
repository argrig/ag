#include "mymatr.h"
#include "mytex.h"
#include <cmath>
#include "myqvect.h"

double abs(myVector& v) {
  return sqrt((v*v).get_d()) ;
}

myVector v_prod (myVector v, myVector w) {
  myVector pr(3) ;
  pr[0] = v[1]*w[2]-v[2]*w[1] ;
  pr[1] = v[2]*w[0]-v[0]*w[2] ;
  pr[2] = v[0]*w[1]-v[1]*w[0] ;
  return pr ;
}

myVector plane_eqn (myVector n, myVector A){
  myVector p_eqn(4) ;
  p_eqn[0]=n[0]; p_eqn[1]=n[1]; p_eqn[2]=n[2];
  p_eqn[3]=(-1)*(n*A) ;
  p_eqn.socr() ;
  if (p_eqn[0]<0 || (p_eqn[0]==0 && p_eqn[1]<0) || (p_eqn[0]==0 && p_eqn[1]==0 && p_eqn[2]<0)){
	p_eqn=(myScalar)(-1)*p_eqn ;
  }
  return p_eqn ;
}

myVector plane_eqn (myVector a, myVector b, myVector A, string param="vvp"){
  if (param=="vvp") {return plane_eqn (v_prod(a,b), A) ;}
  else if (param=="vpp") {return plane_eqn (v_prod(a,A-b),A);}
  else if (param=="ppp") {return plane_eqn (v_prod(A-a,A-b),A);}
}

int have_collin (myMatrix a) {
  myMatrix tmp(2, 3) ;
  
  tmp[0]=a[0] ; tmp[1]=a[1] ;
  int res = (tmp.rk()==1) ;
  
  tmp[0]=a[0] ; tmp[1]=a[2] ;
  res |= (tmp.rk()==1) ;
  
  tmp[0]=a[1] ; tmp[1]=a[2] ;
  res |= (tmp.rk()==1) ;
  
  return res ;
}

int main () {
  myMatrix M(4,3), a(3,3), b(3,3) ;  
  do {
	a.gen_rand(-5,5) ;
  } while (a.rk()<3) ;
  M[0].gen_rand(-5,5);
  M[1]=M[0]+a[0] ;
  M[2]=M[0]+a[1] ;
  M[3]=M[0]+a[2] ;

  b[0]=M[2]-M[1] ;
  b[1]=M[3]-M[1] ;
  b[2]=M[3]-M[2] ;
  
  myMatrix b2=b;
  myVector A(3),B(3),C(3) ;
  myMatrix rkt3(3,3), rkt2(3,2) ;

//	Plane P_0
do {
  b2=b ;
  b2=b2.hash(5,20) ;
  A = M[1] + b2[0] ;
  B = M[1] + b2[1] ;
  C = M[1] + b2[2] ;
} while (have_collin(b2)) ;

  myMatrix P(4,4) ;

cout	<< "Написать общие уравнения следующих плоскостей:\n"
		<< "\\begin {enumerate}\n"
		<< "\\item Плоскости $P_0$, проходящей через точки \\\\ $A_1" ;
		tex_vect(A) ;
cout	<< ",~A_2" ; tex_vect(B) ;
cout	<< ",~A_3" ; tex_vect(C) ; cout << "$\n" ;

P[0]= plane_eqn(M[1],M[2],M[3],"ppp") ;
 

// Plane P_1
  myMatrix a2=a ;
do {
  a2=a ; 
  a2[0]=b[2] ;
  a2=a2.hash(5,20) ;
  A= M[0] + a2[0];
  B=M[0] + a2[1] ;
  C=a2[2] ;
  rkt2[0]=a2[0]-a2[1]; rkt2[1]=C ;
} while (rkt2.rk()<2) ;

cout	<< "\\item Плоскости $P_1$, проходящей через точки \\\\ $A_4" ;
		tex_vect(A) ;
cout	<< ",~A_5" ; tex_vect(B) ;
cout	<< "$ \\\\ параллельно вектору $\\vec{a_1}" ; tex_vect(C) ; 
cout	<< "$\n" ;

P[1]= plane_eqn(M[3],M[2],M[0],"ppp") ;

// Plane P_2
do {
  a2=a ; 
  a2[1]=b[1] ;
  a2=a2.hash(5,20) ;
  A= M[0] + a2[0];
  rkt2[0] = B = a2[1] ;
  rkt2[1] = C = a2[2] ;
} while (rkt2.rk()<2) ;
cout	<< "\\item Плоскости $P_2$, проходящей через точку $A_6" ;
		tex_vect(A) ;
cout	<< "$ с направляющими векторами $\\vec{a_2}" ; tex_vect(B) ;
cout	<< ",~\\vec{a_3}" ; tex_vect(C) ;
cout	<< "$\n" ;

P[2]= plane_eqn(M[3],M[1],M[0],"ppp") ;


// Plane P_3
a2=a ; 
a2[2]=b[0] ;
a2=a2.hash(5,20) ;
B=v_prod(a[0],a[1]); B.socr() ;
A=M[0] + a2[1] ;
cout	<< "\\item Плоскости $P_3$, проходящей через точку $A_7" ;
		tex_vect(A) ;
cout	<< "$ с нормальным вектором $\\vec{a_4}" ; tex_vect(B) ; 
cout	<< "$\n" ;

P[3]= plane_eqn(M[1],M[2],M[0],"ppp") ;

cout << "\\end {enumerate}\n" ;

cout	<< "\nОбозначим через $M_0M_1M_2M_3$ -- пирамиду, "
		<< "получающуюся (доказать!) в пересечении плоскостей $P_0,P_1,P_2,P_3$, "
		<< "причем $M_i\\notin P_i$, а основанием будем считать грань $M_1M_2M_3$. Вычислить:\n" 
		<< "\\begin {enumerate}\n"
		<< "\\item Объем $V$ пирамиды" 
		<< "\\item Высоту $H$ пирамиды опущенную из точки $M_0$" 
		<< "\\item Расстояние $L$ между скрещивающимися ребрами $M_0M_1$ и $M_2M_3$ "
		<< "\\item Длину $h$ апофемы грани $M_0M_2M_3$"
		<< "\\item Острый угол $\\alpha$ между ребром $M_0M_1$ и основанием"
		<< "\\item Острый двухгранный угол $\\beta$ между гранью $M_0M_1M_2$ и основанием"
		<< "\\item Угол при вершине $M_0:~\\gamma=\\angle M_1M_0M_2$"
		;
cout << "\\end {enumerate}\n" ;

comment_matrix(M, "M") ;
comment_matrix(a, "A") ;
comment_matrix(b, "B") ;
comment_matrix(P, "P") ;

double V = abs(a.det1().get_d()/(double)6) ;

myVector n0 = P[0]; n0.pop_back();
myScalar val=n0*M[0]+P[0][3] ;
double H = abs(val.get_d())/abs(n0) ;

myMatrix bb=b ; bb[1]=a[0] ;
val = abs(bb.det1()) ;
myVector prod = v_prod(bb[1],bb[2]) ;
double L = val.get_d()/abs(prod) ;

prod = v_prod(a[2],b[2]) ;
double h = abs(prod)/abs(b[2]) ;

double alpha = asin(abs((n0*a[0]).get_d()/(abs(n0)*abs(a[0])))) ;

myVector n3 = P[3]; n3.pop_back();
double beta = acos((n3*n0).get_d()/(abs(n0)*abs(n3))) ;
beta = (beta>M_PI_2) ? M_PI-beta : beta ;

double gamma = acos((a[0]*a[1]).get_d()/(abs(a[0])*abs(a[1]))) ;

cout << "\n%V=\n%" << V ;
cout << "\n\n%H=\n%" << H ;
cout << "\n\n%L=\n%" << L ;
cout << "\n\n%h=\n%" << h ;
cout << "\n\n%alpha=\n%" << alpha ;
cout << "\n\n%beta=\n%" << beta ;
cout << "\n\n%gamma=\n%" << gamma ;

cerr	<< "Ответ:\n\n"
		<< "Уравнения плоскостей:\\\\\n"
		<< "$P_0:~" ; tex_plane_eqn(P[0], cerr) ; cerr << "$\\\\\n" ;
cerr	<< "$P_1:~" ; tex_plane_eqn(P[1], cerr) ; cerr << "$\\\\\n" ;
cerr	<< "$P_2:~" ; tex_plane_eqn(P[2], cerr) ; cerr << "$\\\\\n" ;
cerr	<< "$P_3:~" ; tex_plane_eqn(P[3], cerr) ; cerr << "$\\\\\n" ;
cerr	<< "Значение искомых величин:\\\\\n" ;
cerr	<< "$V=" << V << ",~H="	<< H << ",~L=" << L << ",~h=" << h
		<< ",~\\alpha=" << alpha << ",~\\beta=" << beta << ",~\\gamma=" << gamma << "$\n";

  return 0 ;
}
