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


#include "mymatr.h"
#include "mypermut.h"

	myPermut::myPermut (unsigned int n):vector<size_t>(n) {
	    for ( size_t i=0; i<n; i++ ) CUR[i]=i ;
	    delim=' ' ;
	}

	void myPermut::transp(size_t i, size_t j){
		size_t temp = CUR[j] ;
		CUR [j] = CUR[i] ;
		CUR [i] = temp ;
	} ;
	
	void myPermut::gen_rand () {
		for (size_t i=size()-1; i>0; i--) {
			transp (i, rand()%(i+1));
		}
	} ;
	myPermut myPermut::rvs() {
	    myPermut b(size()) ;
	    for (size_t i=0; i<size(); i++) {
		b[CUR[i]]=i ;
	    }
	    return b ;
	}
	vector<int> myPermut::circ() {
	    vector<int> res(0) ;
	    size_t n = size() ;
	    vector<int> check(n) ;

	    for (size_t i=0; i<n; i++) { check[i]=0;}
	    size_t k=0 ;
	    for(;k<n;){
		size_t first=k ;
		do {
		    check[k]=1 ;
		    res.push_back(k) ;
		    k=CUR[k] ;
		}while (k!=first) ;
		res.push_back(-1) ;
		for(k=0; k<n && check[k];) k++;
	    }
	    return res ;
	};
	size_t myPermut::inv() {
	    size_t res=0 ;
	    for (size_t i=0; i<size(); i++) {
		for (size_t j=i+1; j<size(); j++) {
		    if(CUR[i]>CUR[j]) res++ ;
		}
	    }
	    return res ;
	}

void tex_permut(myPermut& a, ostream& out) {
	out << "(~" ;
	for (size_t i=0; i<a.size(); i++){ 
		out << (a[i]+1) << "~" ;
	} ;
	out << ")" ;
}


void comment_permut (myPermut& a, const char* name, ostream& out) {
	out <<"\n\%" << name << "=\n%" ;
	for (size_t i=0; i<a.size(); i++){
		out << (a[i]+1) << " " ;
	}	
}

ostream& operator<< (ostream& out, myPermut& a) {
		for (size_t i=0; i<a.size(); i++) {
			out <<  a[i]+1  ;
			if (a.delim) cout << a.delim ;
		}
		return out ;
}

ostream& operator>> (istream& in, myPermut& a) {
		for (size_t i=0; i<a.size(); i++) {
			in >> a[i] ; 
			a[i]-- ;
		}
};

myPermut operator * (const myPermut& a, const myPermut& b) {
	myPermut tmp (a.size()) ;
	for (size_t i=0; i< a.size(); i++) {
		tmp[i] = b[a[i]] ;
	}
	return tmp ;
}
