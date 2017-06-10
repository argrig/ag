#include "mypoly.h"  
// #include "mytex.h"

  
// global functions 

myPolynom monom (size_t n) {
  myPolynom res (n,0) ;
  res[n]=1 ;
  return res ;
}

myScalar mypow (myScalar a, size_t x) {
  myScalar res=1 ;
  for (size_t i=0; i<x; i++) res*=a ;
  return res ;
}

// METHODS

int myPolynom::deg() {
  if (!size()) return -2 ;
  int dg = size() - 1 ;
  CUR.resize(dg+1) ;
  if (dg<0) return dg ;
  while (CUR[dg]==0 && dg) dg-- ;
  return (CUR[dg]!=0) ? dg : -1 ;
} ;

myScalar myPolynom::val(myScalar a) {
    myScalar val=CUR[size()-1] ;
    for (int i=size()-2; i>=0; i--) {
	val=val*a+CUR[i] ;
    }
    return val ;
}

// operators for myPolynom
  myPolynom  operator+ (const myPolynom& p, const myPolynom& q) {
	myPolynom sum, p1=p, q1=q ;
    if (p1.deg() < q1.deg()) {
	  sum = q1 ;
  	  for (size_t i=0; i < p1.size(); i++) {
		sum[i] += p[i] ;
  	  }
    }
	else {
	  sum = p1 ;	  
  	  for (size_t i=0; i < q1.size(); i++) {
		sum[i] += q[i] ;
  	  }
	}
    return sum ;
  };


  myPolynom  operator- (const myPolynom& p, const myPolynom& q) {
	myPolynom p1=p, q1=q ;
	myPolynom sum(q1.deg(),0) ;
    if (p1.deg() < q1.deg()) {
  	  for (size_t i=0; i < p1.size(); i++) {
		sum[i] = p1[i]-q1[i] ;
  	  }
	  for (size_t i=p1.size(); i<q1.size(); i++) {
		sum[i] = -q1[i] ;
  	  }
    }
	else {
	  sum = p1 ;	  
  	  for (size_t i=0; i < q1.size(); i++) {
		sum[i] -= q[i] ;
  	  }
	}
    return sum ;
  };

  myPolynom  operator- (const myPolynom& p) {
	myPolynom res=p;
  	for (int i=0; i <= res.deg(); i++) {
	  res[i] = -res[i] ;
  	}
    return res ;
  };



/*
  istream& operator>> (istream& out, myPolynom& p) {
	myVector tmp=p; out << tmp ;
	return out ;
  } ;
  ostream& operator<< (ostream& in, myPolynom& p) {
	myVector tmp=p; in >> tmp ;
	return in ;
  };
*/

myPolynom operator* (const myPolynom& p, const myPolynom& q) {
  myPolynom p1=p, q1=q ;
  myPolynom res(p1.deg()+q1.deg(), 0) ;
  for (size_t i=0; i<res.size(); i++) {
	for (size_t j=0; j<=i; j++) {
	  if( j < p1.size() && i-j < q1.size() ) res[i]+=(p1[j]*q1[i-j]) ;
	}
  }
  return res ;
};

myPolynom  operator* (const myScalar a, const myPolynom& v) {
  myPolynom tmp(v) ;
  for (size_t i=0; i < v.size(); i++) {
	tmp[i] *= a ;
  }
  return tmp ;		
};


myPolynom* operator/ (const myPolynom& p, const myPolynom& q) {
  myPolynom p1=p, q1=q ;
  myScalar denom ;
  int deg_p = p1.deg(), deg_q = q1.deg() ;
  static myPolynom res[2] ;
  if ( deg_p < deg_q ) {
	res[0]=0; res[1]=p ;
	return res ;
  }
  else {
	int deg_s = deg_p-deg_q ;
	denom = mypow(q1[deg_q], deg_s+1) ;
	p1 = denom*p1 ;
    myPolynom zero(deg_s,0) ;	
	res[0] = zero;
	res[1] = p1 ;
	int cnt = 0 ;
	while (res[1].deg()>=deg_q && deg_s>=cnt) {
	  res[0][deg_s - cnt] = res[1][res[1].deg()]/q1[deg_q] ;
//	  if (deg_s>=cnt) {
		myPolynom debug = (res[0][deg_s - cnt]*monom(deg_s-cnt)) ;
		res[1] = res[1] - q1*debug ;
		cnt++ ;
//	  }
	}
  }
  res[0].deg() ; res[1].deg() ;
  res[0].socr(); res[1].socr() ;
  res[0].idenom *= denom ;
  res[1].idenom *= denom ;
  myScalar nd0 = nod(res[0].idenom, res[0].factor) ; 
  myScalar nd1 = nod(res[1].idenom, res[1].factor) ;
  res[0].factor /= nd0 ;
  res[1].factor /= nd1 ;
  res[0].idenom /= nd0 ;
  res[1].idenom /= nd1 ;
   
  return res ;
};

myPolynom nod(myPolynom p1, myPolynom q1) {

  myPolynom* res=0 ;
  while (q1.deg() != -1) {
	res = p1/q1 ;
	p1 = q1 ;
	q1 = res[1] ;
	myScalar nd_factor = nod (p1.factor, q1.factor) ;
	myScalar nd_denom = nod (p1.idenom, q1.idenom) ;
	p1.factor/=nd_factor ;
	q1.factor/=nd_factor ;
	p1.idenom/=nd_denom ;
	q1.idenom/=nd_denom ;
	
  }

  p1.idenom = 1 ;
  p1.factor = 1 ;
  p1.socr() ;
  if (p1.sen()<0) p1 = -p1 ;
  if (!p1.deg()) p1[0] = 1 ;
  return p1 ;
}
