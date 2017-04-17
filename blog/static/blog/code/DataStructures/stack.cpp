//stack.cpp
//reserve array for fast IO as dynamic allocation can be expensive
#include<iostream>
class StackException: public std::logic_error
{
public:
    StackException(const std::string& message = "StackException")
            : std::logic_error(message)
    {}
};
template<typename Type>
class stack
{
	private:
		//in-class non-static member initialization, C++11 feature
		Type* array=NULL;//preallocated array
		size_t head=0;//1-based index 
		size_t s=0;// size of array
	public:
		stack(size_t t):array(new Type[t]),head(0),s(t){}
		stack():array(NULL),s(0),head(0){}
		~stack()
		{
				delete[] array;
				array=NULL;
		}

		stack(const stack& other)//copy constructor
		{
			if(!other.empty())
			{
				//deep copy
				array=new Type[other.s];
				for(head=0;head<other.head;head++)
					array[head]=other.array[head];
			}
		}

		void swap(stack& lhs, stack& rhs)
		{
			std::swap(lhs.array,rhs.array);
			std::swap(lhs.head,rhs.head);
			std::swap(lhs.s,rhs.s);
		}

		stack& operator=(stack&& other)//move assignment
		{
			swap(*this,other);
			return *this;
		}
		stack& operator=(stack other)//copy and swap 
		{
			swap(*this,other);
			return *this;
		}
		//move constructor
		stack(stack&& other)
		{
			swap(*this,other);
		}

		template<typename T>
		void push(T&& val)//perfect forward
		{
			if(!full())
			{
				++head;
				array[head-1]=std::forward<T>(val);
			}
			else
			{
				throw StackException("StackException: stack overflow !");
			}
		}

		Type& pop()
		{
			if(!empty())
			{
				--head;
				return array[head];
			}
			else
				throw StackException("StackException: stack underflow !");
		}

		Type& top()
		{
			if(!empty())
				return array[head-1];
			else
				throw StackException("StackException: stack empty !");
		}
		size_t size() const//used stack size
		{
			return head;
		}
		bool empty() const
		{
			return head<1;
		}
		bool full() const
		{
			return head>=s;
		}
};

int main(int argn, char** argv)
{
	stack<int> a(4);

	a.push(1);
	a.push(3);
	a.push(4);
	a.pop();

	std::cout<<"stack top element: ";
	std::cout<<a.top()<<std::endl;
	std::cout<<"allocated stack size: ";
	std::cout<<a.size()<<std::endl;
	return 0;
}
