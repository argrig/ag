# include <iostream>
# include <cstdio>
# include <cmath>
using namespace std;

// proiz funktsian hashvum e trvats a(x-x[0])(x-x[1])...(x-x[n]) bazmandami amboxchakan tesqi h-rd andamy
long double proiz(long double[],int,long double,int);

// zn funktsian hashvum e i-erord gumarelii haytarary
long double zn(long double[],int,int);

const int m=50;

main ()
{
	long double eps=0.00099999999;
	long double x[m],y[m];
	long double s[m]={0},temp[m];
	int i,n,j,h;

//INPUT
	printf("Input n\n");
	scanf("%d",&n);
	printf("Input from x[1] to x[n]\n");
	for (i=0;i<n;i++)
		scanf("%lf",&x[i]);
	printf("Input from y[1] to y[n]\n");
	for (i=0;i<n;i++)
		scanf("%lf",&y[i]);


//Main program
	for (i=0;i<n;i++)
	{
		for (h=0;h<i;h++)
			temp[h]=x[h];
		temp[i]=x[n-1];
		for (h=i+1;h<n-1;h++)
			temp[h]=x[h];
		for (j=0;j<n;j++)
			s[j]+=proiz(temp,n-1,y[i]/zn(x,n,i),j);
	}

//OUTPUT
	printf("F(x) = ");
	for(j=0;j<n;j++)
	{
		if ( int(s[j]+eps)-int(s[j]-eps)!=0 )
		{
			if(fabs(s[j]-1)<eps && n-j-1>=1)
			{
				if(n-j-1>=2)
					printf("x^%d",n-j-1);
				else if(n-j-1==1)
					printf("x");
			}
			else
			{
				if(n-j-1>=2)
					printf("%.0lf*x^%d",s[j],n-j-1);
				else if(n-j-1==1)
					printf("%.0lf*x",s[j]);
				else
					printf("%.0lf",s[j]);
			}
			while(j<n-1 && s[j+1]<eps && s[j+1]>-eps)
				j++;
			if(s[j+1]>eps)
				printf("+");
		}
		else if(s[j]>eps || s[j]<-eps)
		{
			if(n-j-1>=2)
				printf("%.3lf*x^%d",s[j],n-j-1);
			else if(n-j-1==1)
				printf("%.3lf*x",s[j]);
			else
				printf("%.3lf",s[j]);
			while(j<n-1 && s[j+1]<eps && s[j+1]>-eps)
				j++;
			if(s[j+1]>eps)
				printf("+");
		}
	}
	printf("\n");
	return 0;
}
long double zn(long double x[],int n,int i)
{
	long double p=1;
	int j;
	for (j=0;j<i;j++)
		p*=(x[i]-x[j]);
	for	(j=i+1;j<n;j++)
		p*=(x[i]-x[j]);
	return p;
}
long double proiz(long double x[],int n,long double koef,int h)
{
	
	long double p[m+10]={0};
	int i, j;
	for (i=0; i<n; i++)
		p[i+1]=0;
	p[0]=1;
	p[1]=-x[0];
	for (i=1; i<n; i++)
		for (j=i+1;j>0;j--)
			p[j]+=(-x[i]*p[j-1]);
	for (i=0; i<n+1; i++)
		p[i]*=koef;
	return p[h];
}