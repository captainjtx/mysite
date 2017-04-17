#include<iostream>
#include<queue>
template<typename Type>
int partition(Type* p,int i, int j)
{
	srand(time(NULL));
	int ind=rand()%(j-i+1)+i;

	Type pivot=p[ind];
	std::swap(p[ind],p[j]);

	int left=i-1;
	int it=i;
	while(it<=j)
	{
		if(p[it]<=pivot)
			std::swap(p[++left],p[it]);
		it++;
	}

	return left;
}
template<typename Type>
void quickSort(Type* p,int i, int j)
{
	std::queue<std::pair<int,int> > q;

	q.push(std::make_pair<int,int>(i,j));

	while(!q.empty())
	{
		int m=q.front().first;
		int n=q.front().second;
		q.pop();

		if(m>=n)
			continue;

		int mid=partition(p,m,n);
		q.push(std::make_pair<int,int>(m,mid-1));
		q.push(std::make_pair<int,int>(mid+1,n));
	}
}
int main(int argn, char** argv)
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
