#pragma once
#include "NodeClass.h"

class HashNode {
public:
	int _key;
	vNode *_value;

	// next bucket with the same key
	HashNode *_next;

public:
	HashNode(int key, vNode* value) : _key(key), _value(value), _next(NULL) {};
	HashNode() { _next = NULL; _key = -1; };

};

class HashMap
{
public:
	int tableSize;
	HashNode *table;

	/*To check if table is full or not*/
	int currentSize;

	HashMap(int a);
	~HashMap();

	/*Generate an index in the range of table*/
	int genKey(const int &key);

	/*Return the required value*/
	bool get(int key, vNode*& value);

	/*Put the value into table*/
	void put(int key, vNode* value);
};