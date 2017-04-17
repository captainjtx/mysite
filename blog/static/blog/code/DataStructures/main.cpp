#include <iostream>

int main(int argn, char** argv)
{
	auto p=std::make_shared<int>(4);
	std::shared_ptr<int> p1=p;

	std::cout<<bool(p1==p)<<std::endl;
	return 0;
}
