#include "HashMap.h"

HashMap::HashMap(int a) {
	tableSize = a;
	currentSize = 0;
	table = new HashNode[tableSize];
};

HashMap::~HashMap() {

	HashNode* temp, *temp1;

	for (int i = 0; i < tableSize; i++) {
		temp = table[i]._next;

		while (temp != NULL) {
			temp1 = temp;
			temp = temp->_next;
			delete temp1;
		}
	}
	delete table;
};

int HashMap::genKey(const int &key)
{
	return (key % tableSize);
}

bool HashMap::get(int key, vNode*& value)
{
	int hashValue = abs(genKey(abs(key)));
	HashNode *entry = &table[abs(hashValue)];

	while (entry != NULL && entry != nullptr) {
		if (entry->_key == key) {
			value = entry->_value;
			return true;
		}
		entry = entry->_next;
	}
	return false;
}

void HashMap::put(int key, vNode* value)
{
	int hashValue = abs(genKey(key));
	HashNode *prev = NULL;
	HashNode *entry = &table[abs(hashValue)];

	if (entry->_key == -1) {
		entry->_key = abs(key);
		entry->_value = value;
		currentSize++;
	}
	else {
		// just update the value
		prev = entry;
		entry = new HashNode(abs(key), value);
		HashNode* temp;
		temp = entry->_next;
		prev->_next = entry;
		entry->_next = temp;
	}
}