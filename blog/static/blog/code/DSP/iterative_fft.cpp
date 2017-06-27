#include<iostream>
#include<math.h>
#include<complex>
#include<vector>

using namespace std;
#define PI 3.14159265

size_t bit_reverse_increment(size_t num, size_t N)
{
	//amortized run time is O(N) since the while loop does not 
	//always loop through log(N) bits 
	N>>=1;
	while(num&N){
		num^=N;
		N>>=1;
	}
	num^=N;
	return num;
}

template<typename Type>
void bit_reverse_copy(const vector<Type>& source, vector<Type>& target)
{
	//assume N is power of 2
	size_t N=source.size();
	size_t rev=0;
	for(int i=0;i<N;++i)
	{
		target[rev]=source[i];
		rev=bit_reverse_increment(rev,N);
	}
}

vector<complex<double> > helper(const vector<complex<double> >& signal, const int sig)
{
	size_t N=signal.size();
	vector<complex<double> > dft_signal(N);
	bit_reverse_copy<complex<double> >(signal, dft_signal);

	int seg=1;
	while(seg<=N)
	{
		auto w=complex<double>(cos(2*PI/seg),sig*sin(2*PI/seg));
		for(int i=0;i<N;i+=seg)
		{
			complex<double> wk(1,0);
			for(int j=0;j<seg/2;++j)
			{
				auto tmp=wk*dft_signal[i+j+seg/2];// save a temporary variable to avoid recomputing 
				auto v=dft_signal[i+j];
				dft_signal[i+j]+=tmp; //butterfly computation
				dft_signal[i+j+seg/2]=v-tmp;
				wk*=w;
			}
		}
		seg<<=1;
	}

	return dft_signal;
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

