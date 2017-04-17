//heapSort.cpp
#include<utility>//swap, c++11
#include<iostream>// cout
#include<time.h>// time CLOCKS_PER_SEC
#include<stdlib.h>// srand, rand

using namespace std;
//the length of array , change it to see different time it takes
#define       NUM            100000

inline int  parent(int i){return i>>1;}
inline int leftChild(int i){return i<<1;}
inline int rightChild(int i){return (i<<1)+1;}

//reorganize the heap to be a maximum heap
//assuming that its left and right subtrees are both maximum heaps
//log(n), n is the heap size
template<typename Type>
void maxHeapify(Type* data,int root,int length)
{
	int l=leftChild(root+1)-1;
	int r=rightChild(root+1)-1;
	//find the maximum of parent, left child and right child
	int max=root;
	if(l<length&&data[root]<data[l])		
		max=l;
	if(r<length&&data[r]>data[max])
		max=r;	
	if(max!=root)
	{
		// if root is less than its children, float down root and recursively call maxHeapify
		std::swap(data[root],data[max]);
		maxHeapify(data,max,length);
	}
}
//build maximum heap from random ordered array
//runs in linear time
template<typename Type>
void buildMaxHeap(Type* data,int length)
{
	for(int i=length/2-1;i>=0;i--)	
		// length/2 to end are leaf nodes
		maxHeapify(data,i,length);
}
//heap sort, nlog(n), order in place
template<typename Type>
void heapSort(Type* data, int length)
{
	//O(n)
	buildMaxHeap(data,length);
	for(int i=length;i>1;i--)	
	{
		std::swap(data[0],data[i-1]);
		maxHeapify(data,0,i-1);
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
	heapSort<unsigned int>(a,NUM);

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
