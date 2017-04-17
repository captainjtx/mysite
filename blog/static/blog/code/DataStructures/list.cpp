//list.cpp requires c++11 lib
#include <iostream>
class ListException: public std::logic_error
{
public:
    ListException(const std::string& message = "ListException")
            : std::logic_error(message)
    {}
};

template<typename Type>
class node 
{
	public:
		Type data;
		std::weak_ptr<node<Type>> prevPtr;//pointer to previous node, use weak pointer to tackle cyclic reference
		std::shared_ptr<node<Type>> nextPtr;//pointer to next node
		node()=default;
		template<typename T>//perfect forward
		node(T&& val):data(std::forward<T>(val)){}
		~node(){/*std::cout<<"delete "<<data<<std::endl;*/}
};
template<typename Type>
class list//doublely linked list
{
	private:
		std::shared_ptr<node<Type>> head;
		std::shared_ptr<node<Type>> tail;
		size_t s=0;
	public:
		template<typename T>//perfect forwarding, deduce T by reference collapsing rule
		void push_back(T&& val)
		{
			try
			{
				auto newNode=std::make_shared<node<Type>>(std::forward<T>(val));
				newNode->prevPtr=tail;
				if(tail)
					tail->nextPtr=newNode;
				else//empty queue 
					head=newNode;
				tail=newNode;
				++s;
			}
			catch(const std::bad_alloc& e)
			{
				throw ListException("ListException: push_back failed with bad_alloc exception");
			}
		}

		template<typename T>//perfect forwarding, deduce T by reference collapsing rule
		void push_front(T&& val)
		{
			try
			{
				auto newNode=std::make_shared<node<Type>>(std::forward<T>(val));
				newNode->nextPtr=head;
				if(head)
					head->prevPtr=newNode;
				else//empty queue 
					tail=newNode;
				head=newNode;
				++s;
			}
			catch(const std::bad_alloc& e)
			{
				throw ListException("ListException: push_front failed with bad_alloc exception");
			}
		}

		void pop_front()
		{
			if(!empty())
			{
				head=std::move(head->nextPtr);
				if(!head)
					tail=nullptr;
				--s;
			}
			else
				throw ListException("ListException: calling pop_front() of empty list");
		}

		void pop_back()
		{
			if(!empty())
			{
				tail=(tail->prevPtr).lock();
				if(tail)
					tail->nextPtr=nullptr;
				else
					head=nullptr;
				--s;
			}
			else
				throw ListException("ListException: calling pop_back() of empty list");

		}

		Type& front()
		{
			if(!empty())
				return head->data;
			else
				throw ListException("ListException: calling front() of empty list");
		}
		Type& back()
		{
			if(!empty())
				return tail->data;
			else
				throw ListException("ListException: calling back() of empty list");
		}

		bool empty() const
		{
			return head==nullptr;
		}
		
		size_t size() const
		{
			return s;
		}

		~list()=default;
		list():s(0){}
		list(const list& other)//copy constructor
		{
			if(!other.empty())
			{
				//deep copy
				head=std::make_shared<node<Type>>(other.head->data);	
				auto pot=other.head->nextPtr;
				auto pct=head;
				s=1;
				while(pot)
				{
					pct->nextPtr=std::make_shared<node<Type>>(pot->data);	
					pct->nextPtr->prevPtr=pct;
					pot=pot->nextPtr;
					pct=pct->nextPtr;
					++s;
				}
				tail=pct;
			}
		}
		//move constructor
		list(list&& other):head(std::move(other.head)),tail(std::move(other.tail)),s(std::move(other.s)){}

		list& operator=(list other)//copy and move, no need to swap for shared_ptr 
		{
			head=std::move(other.head);
			tail=std::move(other.tail);
			s=std::move(other.s);
			return *this;
		}
		list& operator=(list&& other)//move assignment, same with implicit ?
		{
			head=std::move(other.head);
			tail=std::move(other.tail);
			s=std::move(other.s);
			return *this;
		}
};

int main(int argn, char** argv)
{
	list<int> a;

	a.push_back(1);
	a.push_back(3);
	a.push_front(6);
	a.pop_front();
	a.push_front(4);
	a.push_front(4);
	a.pop_back();

	std::cout<<"list front element: ";
	std::cout<<a.front()<<std::endl;
	std::cout<<"list back element: ";
	std::cout<<a.back()<<std::endl;
	std::cout<<"list size: ";
	std::cout<<a.size()<<std::endl;

	return 0;
}
