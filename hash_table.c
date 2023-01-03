#include<stdlib.h>
#include<string.h>

#include "hash_table.h"
#define HT_PRIME_1 151
#define HT_PRIME_2 163

/*
A hash table consist of an array of 'buckets', which stores a key-value pair(element).

The key is passed through a hashing function, so we know the stored location of the key-value pair.

The hashing function returns an integer, which is the pair's index in the array of buckets.

When we want to retrieve a key-value pair, we supply the key to the same hasing function, then get its index, then find the pair in the array by using the index.

This hash table will map string keys to string values (we can map arbitrary key types to arbitrary value types)

Only ASCII strings will be supported, not supporting unicode

*/

/*
API
Associate arrays are a collection of unordered key-value pairs. Duplicate keys are not permitted.
Supporting the following operations:
1. search(a, k) 
return value v associate with key k from the array a, or return null if the key does not exist

2. insert(a, k, v)
store the pair k:v in the array a

3.delete(a, k)
delete the pair k:v associate with k, or do nothing if k does not exist.

*/


//define the initialisation functions for ht_element
//allocate a chunk of memory the size of an ht_element
//save the strings k and v in the new chunk of memory
static ht_element* ht_new_element(const char*k, const char* v) {
	ht_element* i = malloc(sizeof(ht_element));
	i->key = _strdup(k);
	i->value = _strdup(v);
	return i;
}

//ht_new initialises a new hash table
//size defines how many elements we can store
//initiate the array of elements with calloc, which filles the allocated memory with NULL bytes
ht_hash_table* ht_new() {
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));

	ht->size = 53;
	ht->count = 0;
	ht->elements = calloc((size_t)ht->size, sizeof(ht_element*));
	return ht;
}

//functions for deleting ht_item s and ht_hash_tables, which free the memory we've allocated
static void ht_del_item(ht_element* i) {
	free(i -> key);
	free(i->value);
	free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
	for (int i = 0; i < ht->size; i++) {
		ht_element * element = ht->elements[i];
		if (element != NULL) {
			ht_del_item(element);
		}
	}
	free(ht->elements);
	free(ht);
}

/*
hash function:

Take a string as the input and return a number between 0 and m.
m is our desired bucket array length

Variable a should be a prime number larger than the size of the alphabet. We are hashing ASCII strings,
which has an alphabet size of 128, so we should choose a prime larger than that.

Return an even distribution of bucket indexes for an average set of inputs.
If the hash function is unevenly distributed, it will lead to a higher rate of collisions.
Collisions reduce the efficiency ot our hash table.


Two Steps:
1. Convert the string to a large integer
2. Reduce the size of the integer to a fixed range by taking its remander   (mod m)
*/

static int hs_function(const char* s, const int a, const int m) {
	long hash = 0;
	const int len_s = strlen(s);
	for (int i = 0; i < len_s; i++) {
		hash += (long)pow(a, len_s - (i + 1)*s[i]);
		hash = hash % m;
	}
	return (int)hash;
}

/*
Hash Collisions

Hash function map an infinitely larger number of inputs to a finite number of outputs.
Diferent inputs keys may map to the same array index, causing hash collisions.

We use double hashing wo handle collisions.

Double hashing makes use of two hash functions to calculate the index an element sould be stored at after i collisions.
index = (hash_a(string) + i * hash_b(string)) % num_buckets  eq:1

if no collisions have occurred, i = 0, the index is just hash_a of the string;
if a collision happens, the index modified by the hash_b.

hash_b could return 0, reducing the second term to 0, this would lead to the 
hash table try to insert the item into the same bucket over and over, so we could 
add 1 to the result of the second hash, making sure it's never 0.

index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets  eq:2
*/

//fixing hashing collision
static int ht_GetHashIndex(const char*s, const int num_buckets, const int attempt){
	const int hash_a = hs_function(s, HT_PRIME_1, num_buckets);
	const int hash_b = hs_function(s, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;


}

//hash function will implement the following API

// To insert a new key-value pair, we iterate through indexes until we find an empty bucket, 
//then we insert the item into the bucket and increment the hash table's count attribute.
void ht_insert(ht_hash_table* ht, const char* key, const char* value){
	ht_element* element = ht_new_element(key, value);
	int index = ht_GetHashIndex(element->key,ht->size,0);
	ht_element* cur_element = ht->elements[index];
	int i = 1;
	while(cur_element != NULL){  //if cur_element == NULL, means we find an empty bucket, otherwise collision happen
		index = ht_GetHashIndex(element->key, ht->size, i);
		cur_element = ht->elements[index];
		i++;
	}
	ht->elements[index] = element;
	ht->count++;

}
//
char* ht_search(ht_hash_table* ht, const char* key){
	int index = ht_GetHashIndex(key, ht->size, 0);
	ht_element* element = ht->elements[index];// find the specific bucket based on the key and the hash table
	int i = 1; //for collision
	while(element != NULL){

		//if the element's key matches the key we're searching for, we return the element's value.
		if(strcmp(element->key,key) == 0){ 
			return element->value;
		}
		index = ht_GetHashIndex(key, ht->size, i);
		element = ht->elements[index];
		i++;
	}
	return NULL; //it means the while loop hits a NULL bucket, we return NULL, to indicate that no value was found.

}

//we simply mark it as deleted
void ht_delete(ht_hash_table* ht, const char* key){
	
}