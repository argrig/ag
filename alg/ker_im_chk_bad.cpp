#include "mymatr.h"

#define DIM 6

int main () {
// parameters
size_t dim_sum, dim_its, dim_ker, dim_im ; 
cin >> dim_ker >> dim_im >> dim_its >> dim_sum ;

myMatrix  g_ker(dim_ker,DIM,0), g_im(dim_im, DIM,0), g_its(dim_sum, DIM,0), g_sum(dim_its, DIM,0);
myMatrix ug_ker(dim_ker,DIM,0),ug_im(dim_im, DIM,0),ug_its(dim_sum, DIM,0),ug_sum(dim_its, DIM,0);
myMatrix  h_ker(dim_im,DIM,0 ), h_im(dim_ker,DIM,0) ;	 
myMatrix uh_ker(dim_im,DIM,0 ),uh_im(dim_ker,DIM,0) ;	 
  
cin >>  g_ker >>  g_im >>  h_ker >>  h_im >>  g_its >>  g_sum ;
cin >> ug_ker >> ug_im >> uh_ker >> uh_im >> ug_its >> ug_sum ;

if ( ug_ker.rk() == dim_ker && (g_ker.concat(ug_ker)).rk() == dim_ker ) {
	cout << "g_ker" << dim_ker ;
}
cout << g_ker << ug_ker ;
if ( ug_im.rk() == dim_im && (g_im.concat(ug_im)).rk() == dim_im ) {
	cout << "g_im" << dim_im ;
}

if ( uh_ker.rk() == dim_im && (h_ker.concat(uh_ker)).rk() == dim_im ) {
	cout << "h_ker" ;
}

if ( uh_im.rk() == dim_ker && (h_im.concat(uh_im)).rk() == dim_ker ) {
	cout << "h_im" ;
}


if ( ug_its.rk() == dim_its && (g_its.concat(ug_its)).rk() == dim_its ) {
	cout << "g_its" ;
}

if ( ug_sum.rk() == dim_sum && (g_sum.concat(ug_sum)).rk() == dim_sum ) {
	cout << "g_sum" ;
}

 return 0 ;
}
