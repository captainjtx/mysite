//queue.cpp
//reserve array for fast IO as dynamic allocation can be expensive
#include<iostream>
class QueueException: public std::logic_error
{
	public:
		QueueException(const std::string& message = "QueueException")
			: std::logic_error(message)
			{}
};
template<typename Type>
class queue 
{
	private:
		Type* array=NULL;//preallocated array
		size_t head=0;//0-based index 
		size_t tail=0;//0-based index 
		std::size_t s=0;// size of array

	public:
		queue(size_t t):array(new Type[t+1]),s(t+1),head(0),tail(0){}
		queue():array(NULL),s(0),head(0),tail(0){}
		~queue()
		{
			delete[] array;
			s=0;
		}

		queue(const queue& other)//copy constructor
		{
			if(!other.empty())
			{
				//deep copy
				array=new Type[other.s];
				head=other.head;
				tail=head;
				s=other.s;
				while(tail!=other.tail)
				{
					array[tail]=other.array[tail];
					tail=tail>=s-1?0:tail+1;
				}
			}
		}

		void swap(queue& lhs, queue& rhs)
		{
			std::swap(lhs.array,rhs.array);
			std::swap(lhs.head,rhs.head);
			std::swap(lhs.tail,rhs.tail);
			std::swap(lhs.s,rhs.s);
		}

		queue& operator=(queue&& other)//move assignment
		{
			swap(*this,other);
			return *this;
		}
		queue& operator=(queue other)//copy and swap 
		{
			swap(*this,other);
			return *this;
		}
		//move constructor
		queue(queue&& other)
		{
			swap(*this,other);
		}

		template<typename T>
		void enqueue(T&& val)//perfect forward
		{

			size_t tmp=tail>=s-1?0:tail+1;
			if(tmp==head)
				throw QueueException("QueueException: queue overflow !");
			else
			{
				array[tail]=std::forward<T>(val);
				tail=tmp;
			}
		}

		Type& dequeue()
		{
			if(empty())
				throw QueueException("QueueException: queue underflow !");
			else
			{
				size_t tmp=head;
				head=head>=s-1?0:head+1;
				return array[tmp];
			}
		}

		Type& top()
		{
			if(!empty())
				return array[head];
			else
				throw QueueException("QueueException: queue empty !");
		}

		bool full() const
		{
			size_t tmp=tail>=s-1?0:tail+1;
			return tmp==head;
		}
		bool empty() const
		{
			return tail==head;
		}
		size_t size() const//used stack size
		{
			return (tail-head)%s;
		}
};

int main(int argn, char** argv)
{
	queue<int> a(4);

	a.enqueue(1);
	a.enqueue(3);
	a.enqueue(4);
	a.dequeue();

	std::cout<<"queue top element: ";
	std::cout<<b.top()<<std::endl;
	std::cout<<"allocated queue size: ";
	std::cout<<b.size()<<std::endl;
	return 0;
}
