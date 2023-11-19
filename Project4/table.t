#ifndef TABLE_T
#define TABLE_T

#include "table.h"
#include <iostream>
#include <string>
using namespace std;

// for debugging
template <class Key, typename T>
void Table<Key, T>::print()
{
	for (int i = 0; i < tableSize; i++)
	{
		cout << "KEY: " << the_table[i].first.first << " " << the_table[i].first.second
			<< " Values: " << the_table[i].second << endl;
	}
}

// map is a function to map key to address
// in the implementation
// set the function; ie have the code line
// Mapping = map;
// populates table with default values
// for the class Key and T
template <class Key, typename T>
Table<Key, T>::Table(int n, int (*map)(Key k))
{
	tableSize = n;
	Mapping = map;

	the_table = new Pair<Key, T>[n];
	for (int i = 0; i < n; i++)
	{
		the_table[i].first = Key();
		the_table[i].second = T();
	}
}

// return true if item could be added to the
// table false if item was not added.
template <class Key, typename T>
bool Table<Key, T>::insert(Pair<  Key, T >  kvpair)
{
	if (isIn(kvpair.first) != true)
	{
		cout << "kvpair first first: " << kvpair.first.first;
		cout << " kvpair first second: " << kvpair.first.second << endl;
		the_table[Mapping(kvpair.first)] = kvpair;
		numEntries++;
		return true;
	}
	else
	{
		return false;
	}
	//if collision ignore (prob won't be)
}

// erase the key/value pair with the specified key
// from the table and return if successful
// removed item is replaced with default
// values for Key and T
template <class Key, typename T>
bool Table<Key, T>::remove(const Key  aKey)
{
	bool flag = false;
	for (int i = 0; i < tableSize; i++)
	{
		if (the_table[i].first == aKey)
		{
			the_table[i] = 0;
			return 1;
		}
	}
	if (flag == false)
	{
		return 0;
	}
}

// what if key not in table??
template <class Key, typename T>
T  Table<Key, T>::lookUp(const Key aKey)
{
	bool flag = false;
	for (int i = 0; i < tableSize; i++)
	{
		if (the_table[i].first == aKey)
		{
			flag = true;
			return the_table[i].second;
		}
	}
	if (flag == false)
	{
		cout << "Item not in the table. " << endl << endl;
	}
}


//template <class Key, typename T>
//copy constructor
// what is the function defintion..
//just set each index of the table to the initTable, for loop

//template <class Key, typename T>
//destructor
// what is the function defintion..
//delete [] the_table
 
template <class Key, typename T>
void Table<Key, T>::operator= (const Table& initTable)
{
	this->tableSize = initTable.tableSize;
	this->numEntries = initTable.numEntries;
	this->the_table.first = initTable.the_table.first;
	this->the_table.second = initTable.the_table.second;
}

// is the table empty? 
template <class Key, typename T>
bool Table<Key, T>::empty() const
{
	if (numEntries == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
// is the table full?
template <class Key, typename T>
bool Table<Key, T>::full() const
{
	if (numEntries >= tableSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
// return the number of elements in the table
template <class Key, typename T>
int Table<Key, T>::size() const
{
	return numEntries;
}
 
// returns true/false in response to obvious question
template <class Key, typename T>
bool Table<Key, T>::isIn(const Key& key) const
{
	
	for (int i = 0; i < tableSize; i++)
	{
		if (the_table[i].first.first == key.first)
		{
			return true;
		}
	}
	return false;
}

#endif
