//quickSort.cpp
//quick sort nlog(n)

#include<cstdlib>//rand()
#include<utility>//swap, c++11
#include<iostream>// cout
#include<time.h>// time CLOCKS_PER_SEC
#include<stdlib.h>// srand, rand

using namespace std;
//the length of array , change it to see different time it takes
#define       NUM            100000

// Add randomization into the pivot value choosing, expected to acheive an balanced partition 
template<typename Type>
int randomPartition(Type* data,int p, int r)
{ 
	int m=rand()%(r-p+1)+p;//m is randomly chosed between p and r

	std::swap(data[m],data[r]);//move pivot value to the end 

	Type key=data[r];//pivot value

	int i=p-1;//index of left (smaller) subarray
	for(int j=p;j<r;j++)
	{
		if(data[j]<key)	
		{
			std::swap(data[++i],data[j]);
		}
	}
	std::swap(data[++i],data[r]);//exchange the pivot value (end element) and the first element of the right subarray
	return i;
}
template<typename Type>
void quickSort(Type* data, int i, int j)
{
	if(i<j)
	{
		int p=randomPartition(data,i,j);//divide (random partition)

		quickSort(data,i,p-1);//conquer
		quickSort(data,p+1,j);//conquer
	}
	//else return directly for empty or 1-element array, no need to combine
}
//an easier way to call to sort all elements
//num is length of array
template<typename Type>
void quickSort(Type* data, int num)
{quickSort(data,0,num-1);}

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
	quickSort<unsigned int>(a,NUM);
	
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
