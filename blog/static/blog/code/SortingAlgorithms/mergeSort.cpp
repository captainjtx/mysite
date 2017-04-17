//mergeSort.cpp
#include<iostream>// cout
#include<time.h>// time CLOCKS_PER_SEC
#include<stdlib.h>// srand, rand

using namespace std;
//the length of array , change it to see different time it takes
#define       NUM            100000
//merge subroutine combines sorted subarray data[p,...,q] and data[q+1,...,r]
template<typename Type>
void merge(Type* data,int p,int q,int r)
{
	Type *L=new Type[q-p+1];//left side subarray (smaller)
	Type *R=new Type[r-q];//right side subarray (larger)
	//You can add a very large element at the end to avoid checking if subarray is empty
	for(int i=p;i<=q;++i)//copy data into subarrays.
		L[i-p]=data[i];
	for(int i=q+1;i<=r;++i)
		R[i-q-1]=data[i];

	int i=0;//left array index of smallest value
	int j=0;//right array index of smallest value
	for(int k=p;k<=r;k++)//k is the index of output array
	{
		if(L[i]>R[j])
		{
			data[k]=R[j];
			if (++j==r-q)//if right array is empty, concatenate the remaining
			{
				for(int m=i;m<=q-p;++m)
					data[++k]=L[m];
				return;

			}
		}
		else
		{
			data[k]=L[i];
			if (++i==q-p+1)//if left array is empty, concatenate the remaining
			{
				for(int m=j;m<=r-q-1;++m)
					data[++k]=R[m];
				return;

			}
		}
	}
	delete[] L;
	delete[] R;
}
template<typename Type>
void mergeSort(Type* data,int p, int r)
{
	if(p<r)
	{
		int q=int((p+r)/2);//divide
		mergeSort(data,p,q);//conquer
		mergeSort(data,q+1,r);//conquer
		merge(data,p,q,r);//combine
	}
}
//an easier way to call, num is the length of data 
template<typename Type>
void mergeSort(Type* data,int num)
{mergeSort(data,0,num-1);}

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
	mergeSort<unsigned int>(a,NUM);
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
