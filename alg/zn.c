#include <stdio.h>
#include <math.h>
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

int main() {
	int rand = round(random(10)) ;
	int a[3][3], k=0, i, j ;
	for (i=1;i<=3;i+=1)
	       for(j=1;j<=3;j+=1) a[i][j]=k+1 ;
	printf("%d\n%i",rand,det(a)) ;
	return 0 ;
}

int det(int a[3][3]) {
	int res = a[1][1]*a[2][2]*a[3][3]+a[1][2]*a[2][3]*a[3][1]+a[2][1]*a[3][2]*a[1][3]-
		  a[1][3]*a[2][2]*a[3][1]-a[2][1]*a[1][2]*a[3][3]-a[1][1]*a[2][3]*a[3][2];
	return res ;
}
