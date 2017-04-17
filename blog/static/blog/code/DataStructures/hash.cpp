#include<iostream>
using namespace std;
class HashEntry
{
	private:
		int key;
		int value;
	public:
		HashEntry(int key, int value)
		{
			this->key=key;
			this->value=value;
		}
		int getKey()
		{return key;}
		int getValue()
		{return value;}
};

//open addressing implementation
class HashMap
{
	private:
		HashEntry** table;
		int size;
	public:
		HashMap(int size)
		{
			this->size=size;
			table=new HashEntry*[size];
			for(int i=0;i<size;i++)
			{
				table[i]=NULL;
			}
		}
		//linear probe **************************
		int linearProbeGet(int key)
		{
			int initIndex=key%this->size;
			int index=initIndex;
			while(table[index]!=NULL&&table[index]->getKey()!=key)
			{
				index=(index+1)%size;
				//no key in the table, table full
				if(index==initIndex)
					return -1;
			}
			//no key in the table, empty slot
			if(table[index]==NULL)
				return -1;
			return table[index]->getValue();
		}

		int linearProbeSet(int key, int value)
		{
			int initIndex=key%this->size;
			int index=initIndex;
			while(table[index]!=NULL&&table[index]->getKey()!=key)
			{
				index=(index+1)%size;
				if(index==initIndex)
					return -1;
			}
			//overwrite slot with same key
			if(table[index]!=NULL)
				delete table[index];

			table[index]=new HashEntry(key,value);
			return 0;
		}
		//****************************************
		~HashMap()
		{
			for(int i=0;i<this->size;++i)
			{
				delete table[i];
			}
		}

};

int main(int argn, char** argv)
{
	HashMap* map=new HashMap(128);
	map->linearProbeSet(1241,21);
	map->linearProbeSet(21,1);
	map->linearProbeSet(128,0);
	cout<<map->linearProbeGet(2)<<endl;

	delete map;
	return 0;
}
