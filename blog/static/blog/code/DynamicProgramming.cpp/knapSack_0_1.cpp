#include<iostream>
using namespace std;

//brute force
int knapSack(int ind, int* w,int* v, int n, int limit)
{
	if(ind>n-1||limit<=0)
		return 0;
	if(w[ind]>limit)
	{
		ind++;
		return knapSack(ind,w,v,n,limit);
	}
	else
	{
		int choseInd=v[ind]+knapSack(ind+1,w,v,n,limit-w[ind]);
		int noInd=knapSack(ind+1,w,v,n,limit);
		return max(choseInd,noInd);
	}
}
//Dynamic programming
//Overlap can happen when two different selections result the same load
int knapSackDP(int ind, int* w,int* v, int n, int limit)
{
	int Table[n+1][limit+1];
	//initialization
	for(int i=0;i<=limit;++i)
		Table[n][i]=0;
	for(int i=0;i<=n;++i)
		Table[i][0]=0;

	for(int i=n-1;i>=0;--i)
	{
		for(int j=1;j<=limit;++j)
		{
			if(w[i]>j)
				Table[i][j]=Table[i+1][j];
			else{
				Table[i][j]=max(Table[i+1][j],Table[i+1][j-w[i]]+v[i]);
			}
		}
	}
	return Table[0][limit];
}
int main(int argn, char** argv)
{
	int v[3]={60,100,120};
	int w[3]={10,20,30};
	int limit=50;

	cout<<knapSackDP(0,w,v,3,limit)<<endl;

	return 0;
}
