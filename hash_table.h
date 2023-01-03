#pragma once

//each key-value pairs(element) will be stored in ht_element structure

typedef struct {
	char* key;
	char* value;
} ht_element;


//the hash table is an array of pointers to elements
//the size of the array and how full it is.
typedef struct {
	int size;      // size of the array
	int count;	   // numbers of elements in the hash table
	int base_size;
	ht_element** elements;
} ht_hash_table;

// new element
ht_element* ht_new_element(const char*k, const char* v) {

}
ht_hash_table* ht_new_sized(const int base_size){

}

// Initialise a new hash table
ht_hash_table* ht_new() {

}

void ht_resize(ht_hash_table* ht, const int base_size){

}

void ht_resize_up(ht_hash_table* ht){

}

void ht_resize_down(ht_hash_table* ht){

}

//delete ht_element
 void ht_del_element(ht_element* i){

 }

//delete ht_hash_tables
void ht_del_hash_table(ht_hash_table* ht){

}

//define hash function
int hs_function(const char* s, const int a, const int m) {

}

//fixing hashing collision
int ht_GetHashIndex(const char*s, const int num_buckets, const int attempt){

}

//hash function will implement the following API
void ht_insert(ht_hash_table* ht, const char* key, const char* value){

}
char* ht_search(ht_hash_table* ht, const char* key){

}
void ht_delete(ht_hash_table* ht, const char* key){

}
