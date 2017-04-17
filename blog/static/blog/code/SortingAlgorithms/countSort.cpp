//countSort.cpp
#include <cstring>//memcpy
#include <algorithm>//max_element
#include<iostream>// cout
#include<time.h>// time CLOCKS_PER_SEC
#include<stdlib.h>// srand, rand

using namespace std;

//the length of array , change it to see different time it takes
#define       NUM            100000

//this implementation of counting sort requires that data type be a non-negative integer
template<typename Type>
void countSort(unsigned int* A, int length,Type* reorder)//rearrange reorder in the same order with A 
{
	unsigned int* C=new unsigned int[length];
	Type* reorderBackup=new Type[length];

	memcpy(C,A,length*sizeof(unsigned int));
	memcpy(reorderBackup,reorder,length*sizeof(unsigned int));

	unsigned int m=*std::max_element(A,A+length-1);//find the maximum value in output O(n)

	unsigned int* B=new unsigned int[m+1];
	for(int i=0;i<m+1;++i)//initialize B with zeros
		B[i]=0;

	for(int i=0;i<length;++i)//record appearances of A[i] in B[A[i]]
		B[A[i]]++;	
	for(int i=1;i<m+1;++i)//B[i] records how many elements are smaller or equal than i in A
		B[i]+=B[i-1];

	for(int i=length-1;i>=0;--i)//loop from tail of A to make countSort stable
	{
		A[B[C[i]]-1]=C[i];//new A ordered by B
		reorder[B[C[i]]-1]=reorderBackup[i];//record the ordering index
		B[C[i]]--;//update B to position the same element C[i-1] in adjacent place
	}
	delete[] B;
	delete[] C;
}

void countSort(unsigned int* A, int length)
{
	int* order=new int[length];
	countSort(A,length,order);
	delete[] order;
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
	countSort(a,NUM);	
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
