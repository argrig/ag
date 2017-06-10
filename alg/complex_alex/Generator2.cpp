#include <iostream>
#include <complex>
#include <ctime>
#include <cstdlib>

double ads(double a){
	return a>0?a:-a;
}

using namespace std;

int main(){
	complex <double> a,b,c,t1,t2;	
	int pwr=time(NULL)%2+3; //показатель при x
	srand(time(NULL));
	a=complex<double>((rand()%2==0?1:-1)*(rand()%7+1),(rand()%2==0?1:-1)*(rand()%7+1));		//init a
	b=complex<double>((rand()%2==0?1:-1)*(rand()%7+1),(rand()%2==0?1:-1)*(rand()%7+1));		//init b
	c=complex<double>((rand()%2==0?1:-1)*(rand()%7+1),(rand()%2==0?1:-1)*(rand()%7+1));		//init c
	
	cout<<"Найти все корни уравнения: \n\n$ax^{"<<2*pwr<<"}+bx^{"<<pwr<<"}+c=0~~$,\n";
	cout<<" где: \n";
	cout<<"$a="<<a.real(); a.imag()>0?cout<<" + ":cout<<" - "; cout<<abs(a.imag())<<"\\cdot i$; \n";
	cout<<"$b="<<b.real(); b.imag()>0?cout<<" + ":cout<<" - "; cout<<abs(b.imag())<<"\\cdot i$; \n";
	cout<<"$c="<<c.real(); c.imag()>0?cout<<" + ":cout<<" - "; cout<<abs(c.imag())<<"\\cdot i$ \n";
	int i,j,ret;
	
	
	cout<<"%pwr\n%"<<pwr<<endl;
	
	t1=(-b+sqrt(b*b-4.0*a*c))/(2.0*a);	//нахождение кратных корней
	t2=(-b-sqrt(b*b-4.0*a*c))/(2.0*a);	
	
	complex<double>* ans=new complex <double> [2*pwr];	//массив правильных ответов
		
	for(i=0;i<pwr;i++){								//первые корни
		ans[i]=polar(pow(abs(t1),1/double(pwr)),double(arg(t1)+2*M_PI*i)/double(pwr));
	}
	for(i=pwr;i<2*pwr;i++){								//вторые корни
		ans[i]=polar(pow(abs(t2),1/double(pwr)),double(arg(t2)+2*M_PI*i)/double(pwr));
	}
	
	for(i=0;i<2*pwr;i++){			//сортировка ответов по аргументу
		for(j=0;j<2*pwr;j++){
			if((arg (ans[i])>=0 && arg(ans[i])<arg(ans[j]))|| (arg(ans[j])<0 && arg(ans[i])>arg(ans[j]))){
				t1=ans[i];
				ans[i]=ans[j];
				ans[j]=t1;
			}
		} 
	}
	for(i=0;i<2*pwr;i++){			//досортировка отрицательных в обратном порядке
		for(j=0;j<2*pwr;j++){
			if(arg(ans[i])<0 && arg(ans[j])<0 && arg(ans[i])<arg(ans[j])){
				t1=ans[i];
				ans[i]=ans[j];
				ans[j]=t1;
			}
		} 
	}
	for(i=0;i<2*pwr;i++){
		cout<<"%x"<<i+1<<"=\n%"<<ans[i]<<endl;
	}
	cerr<<"Корни Уравнения:"<<endl;
	for(i=0;i<2*pwr;i++){
		cerr<<"$x_"<<i+1<<" ~=~ "<<ans[i].real(); 
		ans[i].imag()>0?cerr<<"+":cerr<<"-";
		cerr<<ads(ans[i].imag())<<"\\cdot i$;\n";
	}
	return 0;
}
  