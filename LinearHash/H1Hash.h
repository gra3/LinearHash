#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>

// THE HASH FUNCTION USED IS ON LINE 49

using namespace std;

class HashNode
{
    public:
    int key;
	int value;
	HashNode* next;
        HashNode(int key, int value) {
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
};

class HashMap
{
    private:
        HashNode** htable;
    public:
		int TABLE_SIZE;
        HashMap(int tableSize) {
			TABLE_SIZE = tableSize;
            htable = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                htable[i] = NULL;
        }

        ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                HashNode* entry = htable[i];
                while (entry != NULL) {
                    HashNode* prev = entry;
                    entry = entry->next;
                    delete prev;
                }
            }
            delete[] htable;
        }

        // Function used to find the key for inserting and searching for elements
        int HashFunc(int value) {
            return value % TABLE_SIZE;
        }

        void insert(int value) {
            int hash_val = HashFunc(value);
            HashNode* prev = NULL;
            HashNode* entry = htable[hash_val];
            while (entry != NULL) {
                prev = entry;
                entry = entry->next;
            }
            if (entry == NULL) {
                entry = new HashNode(hash_val, value);
                if (prev == NULL) {
                    htable[hash_val] = entry;
                }
                else {
                    prev->next = entry;
                }
            }
            else {
                entry->value = value;
            }
        }

        void remove(int val) {
            int hash_val = HashFunc(val);
            HashNode* entry = htable[hash_val];
            HashNode* prev = NULL;
            if (entry == NULL) {
            	cout << val << " is not in the hash." << endl;
                return;
            }

            while (entry->value != val && entry->next != NULL) {
                prev = entry;
                entry = entry->next;
            }

            if (entry->value == val) {
                if (entry->next != NULL) {
                    prev->next = entry->next;
                }
                else {
                    prev->next = NULL;
                }
                delete entry;
                cout << "Element Deleted" << endl;
            }
            else {
                cout << val << " is not in the hash." << endl;
            }
        }

        // Search for the elements in a specified key
        int search(int key)
        {
            bool flag = false;
            int hash_val = HashFunc(key);
            HashNode* entry = htable[hash_val];
            while (entry != NULL) {
                if (entry->key == key) {
                    cout << entry->value << " ";
                    flag = true;
                }
                entry = entry->next;
            }
            if (!flag)
                return -1;
        }

        bool searchVal(int val) {
            int hash_val = HashFunc(val);
            HashNode* entry = htable[hash_val];
            while (entry != NULL) {
                if (entry->value == val) {
                    cout << val << " is in the hash." << endl;
                    return true;
                }
                entry = entry->next;
            }
            cout << val << " is not in the hash." << endl;
            return false;
        }
};