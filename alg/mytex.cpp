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
            *  Copyright (C) 2003 - 2009                     *
            \************************************************/


#include "mytex.h"
void tex_matrix(myMatrix& Y, ostream& out) {
	register size_t k=Y.size() ;
	register size_t n=Y[0].size() ;
	string arr_param(n,'r')  ;
	out << "\\left(\n" ;
	out << "\\begin {array} {" <<arr_param<<"}\n" ;
	for (size_t i=0; i<k; i++){
		for (size_t j=0; j<n; j++){
		const char* delim = (j) ? " & " : "" ;
			out << delim ;
			out << Y[i][j] ;
		}
		out << " \\\\\n" ;
	}
	out << "\\end {array}\n" ;
	out << "\\right)\n" ;
} ;

void comment_matrix (myMatrix& X, const char* name, ostream& out) {
	out <<"\n\%" << name << "=" << endl;
	for (size_t i=0; i<X.size(); i++){
		out << "% " << X[i] << endl;
	}	
}

void tex_equation (myMatrix Y) {
	size_t k = Y.size() ; //equations number
	size_t n = Y[0].size()-1 ; //variables number
	string arr_param(2*n+1,'r')  ;
	cout << "$$\n\\begin {array} {" << arr_param << "}\n" ;
	for (size_t i=0; i<k; i++){
		for (size_t j=0; j<n+1; j++){
			if (j) {
				char* sign = "   "  ; 
				if ( Y[i][j] > 0 ) sign = " + " ;
				if ( Y[i][j] < 0 && j<n) {sign = " - " ;	Y[i][j] = -Y[i][j] ; }
				if (j==n) sign = " = " ;				
				cout << " & " << sign << " & " ;
			}
			if ( Y[i][j]!=0 || j==n ) {
				if ( Y[i][j] != 1 || j==n ) cout << Y[i][j] ;
				if (j < n) {
					cout << "x_" << j+1 ;
				}
			}
		}
		cout << " \\\\\n" ;
	}
	cout << "\\end {array}\n$$\n" ;
} ;


void tex_polynom(myPolynom Y, int mod, ostream& out, char var) {
  int k=Y.deg() ;
  if (k==-1) { out << 0 ; return ; }
  int not_first=0 ;
if (!mod) {
  for (int i=0; i<=k; i++){
	  Y[i]*=Y.factor ;
	  if (Y[i]==0) continue ;
	  if (Y.idenom*Y[i]>0) {
		if (not_first) out << "+" ;
	  }
	  else if(Y.idenom*Y[i]<0) out << "-" ;
	  not_first=1;
	  myScalar dd = nod(Y.idenom,Y[i]) ;
	  if (abs (Y.idenom/dd) == 1) {
		if (abs(Y[i]/dd) != 1 || !i) out << abs(Y[i]/dd) ;
	  }
	  else out << "\\frac {" << abs(Y[i]/dd) << "} {" << abs(Y.idenom/dd) << "}" ;
	  if (i) { 
		out << var ;
		if (i!=1) out << '^' << i ;
	  }
  }
}
else {
  myScalar factor = abs (Y.factor/nod(Y.idenom, Y.factor)) ;
  myScalar idenom = abs (Y.idenom/nod(Y.idenom, Y.factor)) ;
  bool need_br = ! (factor==1 && idenom==1) ;
  char sign = (Y.idenom*Y.factor<0) ? '-' : ' ' ;
  out << sign ;
  if (need_br) out<< "\\frac{" << factor << "}{" << idenom << "}\\left( " ;
  for (int i=0; i<=k; i++) {
	if (Y[i]==0) continue ;
	if (Y[i]>0 && not_first) { out << "+" ;}
	not_first=1;
	if ( Y[i]!=1 || !i ) out << Y[i] ;
	if (i) { 
	  out << var ;
	  if (i!=1) out << '^' << i ;
	}
  }
  if (need_br) out << "\\right)" ;
}
} ;

void tex_comb(myPolynom Y, int mod, ostream& out, char var) {
  int k=Y.deg() ;
  if (k==-1) { out << 0 ; return ; }
  int not_first=0 ;
if (!mod) {
  for (int i=0; i<=k; i++){
	  Y[i]*=Y.factor ;
	  if (Y[i]==0) continue ;
	  if (Y.idenom*Y[i]>0) {
		if (not_first) out << "+" ;
	  }
	  else if(Y.idenom*Y[i]<0) out << "-" ;
	  not_first=1;
	  myScalar dd = nod(Y.idenom,Y[i]) ;
	  if (abs (Y.idenom/dd) == 1) {
		if (abs(Y[i]/dd) != 1) out << abs(Y[i]/dd) ;
	  }
	  else out << "\\frac {" << abs(Y[i]/dd) << "} {" << abs(Y.idenom/dd) << "}" ; 
	  out << "\\vec{" << var << "}";
	  out << '_' << i+1 ;
  }
}
else {
  myScalar factor = abs (Y.factor/nod(Y.idenom, Y.factor)) ;
  myScalar idenom = abs (Y.idenom/nod(Y.idenom, Y.factor)) ;
  bool need_br = ! (factor==1 && idenom==1) ;
  char sign = (Y.idenom*Y.factor<0) ? '-' : ' ' ;
  out << sign ;
  if (need_br) out<< "\\frac{" << factor << "}{" << idenom << "}\\left( " ;
  for (int i=0; i<=k; i++) {
	if (Y[i]==0) continue ;
	if (Y[i]>0 && not_first) { out << "+" ;}
	not_first=1;
	if ( Y[i]!=1 || !i ) out << Y[i] ;
	out << "\\vec{"<< var << "}";
	out << '_' << i+1 ;
  }
  if (need_br) out << "\\right)" ;
}
} ;


void tex_plane_eqn (const myVector& line, ostream& out) {
  string sign ;
  if (line[0]!=0) {
	if (line[0]<0) {out << "-" ;}  
	if (abs(line[0])!=1) out << abs(line[0]) ;
	out << "x" ;
	sign="~+~" ;
  }
  else 	sign="" ;

  if (line[1]!=0) {
  	out << ( (line[1]>0) ? sign : "~-~" ) ;
	if (abs(line[1])!=1) out << abs(line[1]) ;
	out << "y" ;
  }
  
  if (line[2]!=0) {
  	out << ( (line[2]>0) ? sign : "~-~" ) ;
	if (abs(line[2])!=1) out << abs(line[2]) ;
	out << "z" ;
  }
  
  if (line[3]!=0) {
  	out << ( (line[3]>0) ? "~+~" : "~-~" ) ;
	out << abs(line[3]) ;
  }
  out << "~=~0" ;
} ;

void tex_vect(const myVector& x, ostream& out) {
  	out << "(~" ;
	for (int i=0; i<x.size(); i++) {
	  if (i) out << ";~";
	  out << x[i] ;
	}
	out << "~)" ;
} ;

void tex_kv_frm (const myMatrix& Q, ostream& out) {
  char sign=' ' ;
  for(size_t i=0; i<Q.size(); i++){
	for(size_t j=i; j<Q.size(); j++) {
	  if ( Q[i][j]<0 ) {sign='-';}
	  else	if ( Q[i][j]>0 && (i!=0 || j!=0) ) {sign='+';}
			else {sign= ' ';}
	  myScalar val=abs(Q[i][j]) ;
	  if (i==j && Q[i][j]!=0 )
		{ out << sign ;
		  if (val != 1) {out << val ;} 
		  out << " x^2_" << (i+1) ;
		}
	  else if ( Q[i][j]!=0 ) 
		{ out << sign << (2*abs(Q[i][j])) << "x_" << (i+1) << "x_" << (j+1); }
	}
  }
}


void tex_surf (const myMatrix& Q, const myVector& b, const myScalar c, ostream& out ) {
  char sign=' ' ;
  for(size_t i=0; i<Q.size(); i++){
	for(size_t j=i; j<Q.size(); j++) {
	  if ( Q[i][j]<0 ) {sign='-';}
	  else	if ( Q[i][j]>0 && (i!=0 || j!=0) ) {sign='+';}
			else {sign= ' ';}
	  myScalar val=abs(Q[i][j]) ;
	  if (i==j && Q[i][j]!=0 )
		{ out << sign ;
		  if (val != 1) {out << val ;} 
		  out << " x^2_" << (i+1) ;
		}
	  else if ( Q[i][j]!=0 ) 
		{ out << sign << (2*abs(Q[i][j])) << "x_" << (i+1) << "x_" << (j+1); }
	}
  }
  for (size_t i=0; i<b.size(); ++i) {
    if (b[i] > 0)  { out << '+'; } ;
    if (b[i] != 0) { out << b[i] << "x_" << (i+1) ; } ;
  }
  if (c>0) {out << '+';} ;
  if (c != 0) {out << c ;} ;
  out << " = 0" ;
}
