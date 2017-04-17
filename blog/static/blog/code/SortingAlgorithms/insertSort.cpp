//insertSort.cpp
#include<iostream>// cout
#include<time.h>// time CLOCKS_PER_SEC
#include<stdlib.h>// srand, rand

using namespace std;
//the length of array , change it to see different time it takes
#define       NUM            100000
template<typename Type>
void insertSort(Type* data,int length)
{
	Type key;
	for(int i=1;i<length;++i)
	{
		key=data[i];
		int j;
		//insert key into data[1,...i-1]
		for(j=i-1;j>=0;--j)
		{
			if(key>data[j])
				break;
			data[j+1]=data[j];
		}
		data[j+1]=key;
	}
}

//1,returns error message if it failed
//2,returns the elapsed time in seconds
int main(int argn,char** argv)
{
	unsigned int a[NUM];
	double start,end;
	//generate pseudo random number
	srand(time(NULL));
	for(int i=0;i<NUM;++i)
		a[i]=rand()%10000;
		
	//get the starting clock tick 
	start=clock();
	insertSort<unsigned int>(a,NUM);
	
	//get the ending clock tick 
	end=clock();

	cout<<endl;
	//output error if there is a misorder 
	for(int i=1;i<NUM;++i)
	{
		if(a[i]<a[i-1])
			cout<<"error";
	}
	//output the time in seconds 
	cout<<"Total time cost:"<<(end-start)/CLOCKS_PER_SEC<<" s"<<endl;

}
