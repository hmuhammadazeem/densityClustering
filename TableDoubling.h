#pragma once
#include "HashMap.h"


void tableDoubling(HashMap*& t) {
	int oldSize = t->tableSize;
	HashMap *table2 = new HashMap(oldSize * 2);
	HashNode *temp;

	for (int i = 0; i < oldSize; i++) {
		table2->put(t->table[i]._key, t->table[i]._value);
		temp = t->table[i]._next;
		while (temp != NULL) {
			table2->put(temp->_key, temp->_value);
			temp = temp->_next;
		}
	}
	HashMap* temp1 = t;
	t = table2;
	delete temp1;
	table2 = NULL;
	temp1 = NULL;
}

//DJB2 Algorithm
int HashKey(string value) {
	int hashAddress = 5224;
	for (int i = 0; i < value.length(); i++) {
		hashAddress = ((hashAddress << 5) + hashAddress) + value[i];
	}
	return hashAddress;
}
