# include <iostream>
# include <vector>
# include <ctime>
# include <algorithm>
using namespace std;
int main()
{
	vector <int>a,x,y;
	srand (time(NULL));
	int i,b,t,j,m;
	int n=rand()%2+3;
	int k=(n==3?8:6);
	bool p;
	do
	{
		b=rand()%2;
		if(b==0)
			t=-rand()%k;
		else
			t=rand()%k;
	}while(t==0);
	a.push_back(t);
	for(i=1;i<=n;i++)
	{
		b=rand()%2;
		if(b==0)
			a.push_back(-rand()%k);
		else
			a.push_back(rand()%k);
	}
	for(i=0;i<(n+1)/2;i++)
	{
		b=a[i];
		a[i]=a[n-1-i];
		a[n-i]=b;
	}
	k-=3;
	for(i=0;i<=n;i++)
	{
		b=rand()%2;
		if(b==0)
			t=-rand()%k;
		else
			t=rand()%k;
		p=true;
		for(j=0;j<x.size();j++)
			if(x[j]==t)
			{
				p=false;
				break;
			}
		if(!p)
		{
			i--;
			continue;
		}
		x.push_back(t);
		m=0;
		for(j=n;j>=0;j--)
		{
			m*=t;
			m+=a[j];
		}
		y.push_back(m);
	}
	for(i=0;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	for(i=0;i<=n;i++)
		cout<<x[i]<<" ";
	cout<<endl;
	for(i=0;i<=n;i++)
		cout<<y[i]<<" ";
	cout<<endl;
	return 0;
}