#include<iostream>
#include<math.h>
#include<complex>
#include<vector>

using namespace std;
#define PI 3.14159265

vector<complex<double> > helper(const vector<complex<double> >& signal, const int sig)
{
	size_t len=signal.size();
	if(len==1)
		return signal;
	vector<complex<double> > odd(len>>1);
	vector<complex<double> > even(len>>1);
	for(size_t i=0;i<len;++i)
	{
		if(i%2)
			odd[(i-1)>>1]=signal[i];
		else
			even[i>>1]=signal[i];
	}

	//divide and conquer
	vector<complex<double> > dft_odd=helper(odd,sig);
	vector<complex<double> > dft_even=helper(even,sig);

	//merge
	vector<complex<double> > dft_all(len,0);
	complex<double> w;
	w=complex<double>(cos(2*PI/len),sig*sin(2*PI/len));
	complex<double >wk(1,0);
	
	for(int i=0;i<len/2;++i)
	{
		auto tmp=wk*dft_odd[i];// save a temporary variable to avoid recomputing 
		dft_all[i]=dft_even[i]+tmp;// key operations
		dft_all[i+len/2]=dft_even[i]-tmp; 
		wk*=w;
	}
	return dft_all;
}

vector<complex<double> > zero_padding(vector<complex<double> > signal)
{
	//implicit copy of signal
	size_t len=signal.size();
	if(len-1&len)//not power of 2, zero-padding
	{
		while(len&len-1)len&=len-1;
		len<<=1;//assume size_t is big enough, overflow is not checked here
		signal.resize(len,{0,0});
	}
	return signal;
}

//recursive fft
vector<complex<double> > fft(const vector<complex<double> >& x)
{
	vector<complex<double> > s=zero_padding(x);
	return helper(s,-1);
}

//inverse fft
vector<complex<double> > ifft(const vector<complex<double> >& X)
{
	auto x=helper(X,1);
	size_t N=X.size();
	for(auto& e:x)
		e/=N; //scale factor N

	return x;
}
int main(int argn, char** argv)
{
	//a cosine wave with frequency 1 Hz sampled at N Hz
	int N=6;
	vector<complex<double> > s(N,{0,0});
	for(int i=0;i<N;++i)
	{
		s[i]={cos(2*PI*i/N),0};
	}
	auto S=fft(s);
	auto IS=ifft(S);

	cout<<"original signal of length: "<<s.size()<<endl;
	for(auto c:s)
	{
		cout<<c<<" ";
	}
	cout<<endl<<endl<<"fft of length: "<<S.size()<<endl;
	for(auto c:S)
	{
		cout<<c<<" ";
	}
	cout<<endl<<endl<<"ifft of length: "<<IS.size()<<endl;
	for(auto c:IS)
	{
		cout<<c<<" ";
	}
	cout<<endl;
	return 0;
}

