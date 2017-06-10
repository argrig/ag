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

int main () {
    const size_t sz=9 ;
    
    myVector empty(0) ;
    myPermut a(sz), x(sz) ;
	
    a.gen_rand() ;
    x.gen_rand() ;
    size_t left = rand()%2 ;
    string eqn = (left) ? "$x\\cdot a=b$":"$a\\cdot x=b$" ;
    myPermut b = (left) ? x*a : a*x ;
    
    cout << "Решить уравнение " << eqn
	 << " и вычислить четность, число инверсий, декремент, разложение в "
	 << " произведение циклов и транспозиций для решения:" ;
    cout << " \n\\begin{eqnarray*}\n" ;
	cout << "a~=~" ; tex_permut(a) ; cout << "\\\\\n" ;
	cout << "b~=~" ; tex_permut(b) ; cout << "\n" ;
    cout << "\\end{eqnarray*}\n" ;
    
    myPermut a_rvs=a.rvs() ;
    vector<int> circ=x.circ() ;

    
    cerr << "Ответ:\n\n" ;
    cerr << "$a^{-1}~=~" ; tex_permut(a_rvs, cerr) ; cerr << "$\n\n" ;
    cerr << "$x~=~" ; tex_permut(x,cerr) ; cerr << "$\n\n" ;
    cerr << "Разложение в произведение циклов: $x~=~[" ;
    size_t c_cnt=1 ;
    for (size_t i=0; i<circ.size()-1; i++) {
	if (circ[i]>=0) { cerr << (circ[i]+1); }
	else {cerr << "]["; c_cnt++;}
    }
    cerr << "]$\n\n" ;

    size_t dcr=sz-c_cnt ;
    size_t inv=x.inv() ;
    cerr << "Декремент: " << dcr ; cerr <<"\n\n" ;     
    cout << "%dcr=\n%" << dcr;
    comment_permut (a_rvs, "a_rvs") ;
    comment_permut (x, "x") ;
    cout << "\n%circ=\n%" ;
    for (size_t i=0; i<circ.size(); i++) {cout << (circ[i]+1)<< " " ;} ;
    cout << "\n%inv=\n%" << inv ;

    cerr << "Разложение в произведение транспозиций:\n$$x~=~" ;
    for (size_t i=0; i<circ.size()-1; i++) {
	size_t first = circ[i]+1;
	while (circ[++i]>=0) {
	    cerr << "(" << first << (circ[i]+1)<< ")" ;
	}
    }
    cerr << "\n$$\n" ;
    cerr << "\nЧисло инверсий: " << inv ;
}
