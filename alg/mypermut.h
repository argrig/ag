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


#ifndef MYPERMUT_H 
#define MYPERMUT_H 

class myPermut : public vector <size_t> {
public :
	char delim ;
	myPermut(unsigned int) ;
	inline void transp(size_t i, size_t j);
	void gen_rand () ;
	myPermut rvs() ;
	vector<int> circ() ;
	size_t inv() ;
} ;

void tex_permut(myPermut& a, ostream& out=cout) ;
void comment_permut (myPermut& a, const char* name, ostream& out=cout) ;

ostream& operator<< (ostream& out, myPermut& a) ;
ostream& operator>> (istream& in, myPermut& a) ;
myPermut operator * (const myPermut& a, const myPermut& b) ;

#endif /*MYPERMUT_H*/
