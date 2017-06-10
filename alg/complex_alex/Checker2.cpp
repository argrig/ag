#include <iostream>
#include <complex>

#define Mistake 0.001

int pten(int p){
	int ret=1;
	for(int i=0;i<p;i++){
		ret*=10;
	}
	return ret;
}

using namespace std;

int main ()
{
	int i,j,pwr,ret;			//ret содержит данные о совпадениях с генерированными корнями; порядок корней - справа налево
								//число на i-ом мест означает данные о совпадении i-ого корня формат: 0 - неверно; 1 - ошибка четверти; 2 - все верно
	cin>>pwr;					//Считывание Типа задачи т.е. (3 или 4)
	complex<double>* ansg=new complex<double>[2*pwr];
	complex<double>* ansu=new complex<double>[2*pwr];
	
	for(i=0;i<2*pwr;i++){
		cin>>ansg[i]; 
	}
															//считывание генерированных ответов	формат (Re,Im)
	for(i=0;i<2*pwr;i++){
		cin>>ansu[i];						
			for(j=0;j<2*pwr;j++){			
				if(abs(ansu[i]-ansg[j])<=Mistake){
				ret+=pten(i);
				ansg[j]=complex<double>(0,0);	
				if(i==j) ret+=pten(i);
				break;	
				}
			}
	}														//ввод и сравнение пользовательских ответов формат (Re,Im)
	for(i=0;i<2*pwr;i++){	
		switch 	((ret/pten(i))%10){							
		case 2:cout<<"x_"<<i+1<<" вычислен верно";break;											
		case 1:cout<<"x_"<<i+1<<" имеет правильное значение, но не на правильном месте";break;
		case 0:cout<<"x_"<<i+1<<" вычислен неверно";break;
		default: cout<<"x_"<<i+1<<" ошибка ввода";
		}									
		cout<<endl;																							
	}
	cout<<ret;
	return ret;
}

