#include<iostream>
#include<stack>
#include<ctime>
template<typename Type>
int partition(Type* p,int left, int right)
{
	//random partition
	srand(time(NULL));
	int ind=rand()%(right-left+1)+left;
	Type pivot=p[ind];

	std::swap(p[ind],p[right]);
	int i=left-1;
	int j=left;

	while(j<=right)
	{
		if(p[j]<=pivot)
			std::swap(p[++i],p[j]);
		
		j++;
	}
	return i; 
}
template<typename Type>
void quickSort(Type* p,int i,int j)
{
	std::stack<int> s;
	s.push(i);
	s.push(j);

	while(!s.empty())
	{
		int right=s.top();
		s.pop();
		int left=s.top();
		s.pop();

		if(left>=right)
			continue;
		int ind=partition(p,left,right);
		s.push(left);
		s.push(ind-1);

		s.push(ind+1);
		s.push(right);
	}
}
int main(int arg, char** argv)
{
	int p[10]={1,10,2,3,-1,2,-10,24,51,-30};
	int len=10;

	std::cout<<"Original Array: ";
	for(int i=0;i<len;++i)
		std::cout<<p[i]<<" ";
	std::cout<<std::endl;
	quickSort(p,0,len-1);

	std::cout<<"Sorted Array: ";
	for(int i=0;i<len;++i)
		std::cout<<p[i]<<" ";
	std::cout<<std::endl;
	return 0;
}
