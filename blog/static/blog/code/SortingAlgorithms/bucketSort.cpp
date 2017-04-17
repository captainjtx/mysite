//bucketSort.cpp
#include <cmath>//floor
#include <list>//list
#include <algorithm>//copy max_element min_element 
#include<time.h>// time CLOCKS_PER_SEC
#include<iostream>// cout
#include<stdlib.h>// srand, rand

using namespace std;
//the length of array , change it to see different time it takes
#define       NUM            100000

void bucketSort(unsigned int* data,int length)
{
	//buckets store the sublists of each bin
	std::list<unsigned int>* buckets=new std::list<unsigned int>[length];

	double a=clock();
	unsigned int m=*std::max_element(data,data+length-1);//O(n)
	unsigned int mn=*std::min_element(data,data+length-1);//O(n)
	std::cout<<"Min/Max time: "<<(clock()-a)/CLOCKS_PER_SEC<<std::endl;

	int ind=0;

	a=clock();
	for(int i=0;i<length;++i)//divide data input into n=length buckets
	{
		ind=floor(float(data[i]-mn)/(m-mn)*(length-1));
		
		std::list<unsigned int>::const_iterator iterator=buckets[ind].begin();
		while(iterator!=buckets[ind].end()&&*iterator<=data[i])
			++iterator;
	      	//return the position to insert (online insertion sort)
		buckets[ind].insert(iterator,data[i]);
	}
	std::cout<<"Insert time: "<<(clock()-a)/CLOCKS_PER_SEC<<std::endl;
	
	int list_len=0;
	a=clock();
	for(int i=0;i<length;++i)//combine sorted sublists
	{
		copy(buckets[i].begin(),buckets[i].end(),data+list_len);
		list_len+=buckets[i].size();
	}
	std::cout<<"Combine time: "<<(clock()-a)/CLOCKS_PER_SEC<<std::endl;
	delete [] buckets;
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
	bucketSort(a,NUM);
	
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
