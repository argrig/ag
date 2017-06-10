#include <mymatr.h>
#include <mytex.h>

int main () {
	myVector empty(0) ;
	const size_t n=3;
        size_t modulo ;
	int res=0 ;
	
	myMatrix A(n,n) ;
	myVector x(n), b(n), b1(n) ;
	cin >> A >> b >> x >> modulo;
	b1=A*x ;
	for (size_t i=0;i<n;i++) {
		if ((b1[i]-b[i])%modulo == 0) {
			res++ ;
		}
	}
	cout << res ;
	return res ;
}

