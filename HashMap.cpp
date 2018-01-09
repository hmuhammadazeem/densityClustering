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

bool HashMap::get(int key, vNode*& value, std::string name)
{
	int hashValue = abs(genKey(abs(key)));
	HashNode *entry = &table[abs(hashValue)];

	while (entry != NULL) {
		if (entry->_key == abs(key)) {
			if (entry->_value->name == name) {
				value = entry->_value;
				return true;
			}
		}
		entry = entry->_next;
	}
	return false;
}

void HashMap::put(int key, vNode* value)
{
	int hashValue = abs(genKey(key));
	HashNode *temp = NULL;
	HashNode *entry = &table[abs(hashValue)];


	if (entry->_key == -1) {
		entry->_key = abs(key);
		entry->_value = value;
		currentSize++;
	}
	else {
		HashNode* _new = new HashNode(abs(key), value);
		HashNode* temp;
		temp = entry->_next;
		entry->_next = _new;
		_new->_next = temp;
	}
}

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
int HashKey(std::string value) {
	int hashAddress = 5685;
	for (int i = 0; i < value.length(); i++) {
		hashAddress = ((hashAddress << 5) + hashAddress) + value[i];
	}
	return hashAddress;
}

void HashMap::Delete(int key, std::string name) {

	int hashValue = abs(genKey(abs(key)));
	HashNode *entry = &table[abs(hashValue)];

	HashNode* next = entry->_next; HashNode* temp = entry;

	if ((entry->_key == abs(key)) && entry->_value->name == name) {
		if (next == NULL) {
			entry->_key = -1;
			entry->_next = NULL;
			entry->_value = NULL;
		}
		else
		{
			entry->_key = next->_key;
			entry->_next = next->_next;
			entry->_value = next->_value;
		}
		delete next;
		next = NULL;
	}
	else {
		while (next != NULL) {
			if (next->_key == abs(key)) {
				if (next->_value->name == name) {
					break;
				}
			}
			next = next->_next;
			temp = temp->_next;
		}
		temp->_next = next->_next;
		delete next;
		next = NULL;
	}
}