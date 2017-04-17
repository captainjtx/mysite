#include<iostream>
using namespace std;
int main(int argn, char** argv)
{
	int** d=new int*[10];
	for(int i=0;i<10;i++)
	{
		if(d[i]==NULL)
		cout<<d[i]<<endl;
		d[i]=NULL;
	}
	for(int i=0;i<10;i++)
	{
		delete[] d[i];
	}
	return 0;
}
