#include "hash.h"
#include "list.c"


// create a new hashtable; parameter is a size hint
hashtable_t *hashtable_new(int sizehint) {
	int size = hashtable_size_calculator(sizehint);
	//Allocate the table itself
	hashtable_t *table = malloc(sizeof(hashtable_t));
	//Set the table's attributes
	table->size = size;
	//Set up an array of bucket pointers and null-terminate
	table->buckets = malloc(sizeof(list_t*)*(size+1));
	table->buckets[size] = NULL;
	int i = 0;
	for(;i<=size;i++){
		table->buckets[i] = malloc(sizeof(list_t));
		list_init((list_t*)table->buckets[i]);
	}
	//Initialize the table's lock
	pthread_mutex_init(&table->globalLock, NULL);
     	return table;
}
int hashtable_size_calculator(int sizehint){
	if(sizehint < 17){
		return 17;
	}
	else if (sizehint < 31){
		return 31;
	}
	else if (sizehint < 53){
		return 53;
	}
	else if (sizehint < 71){
		return 71;
	}
	else if (sizehint < 173){
		return 173;
	}
	else if (sizehint < 281){
		return 281;
	}
	else if (sizehint < 409){
		return 409;
	}
	else if (sizehint < 541){
		return 541;
	}
	else if (sizehint < 659){
		return 659;
	}
	else if (sizehint < 809){
		return 809;
	} 
	else if (sizehint < 941){
		return 941;
	}
	else if (sizehint < 1069){
		return 1069;
	} else {
		return sizehint;
	}
}
// free anything allocated by the hashtable library
void hashtable_free(hashtable_t *hashtable) {
	int i = 0;
	for(;i<(hashtable->size);i++){
		list_clear((list_t*)hashtable->buckets[i]);
		free(hashtable->buckets[i]);
	}
	free(hashtable->buckets);
	free(hashtable);
}

// add a new string to the hashtable
void hashtable_add(hashtable_t *hashtable, const char *s) {
	pthread_mutex_lock(&hashtable->globalLock);
	int key = hash(s);
	key = key % (hashtable->size);
	//put the string into the bucket
	list_add((list_t *)hashtable->buckets[key], s);
	pthread_mutex_unlock(&hashtable->globalLock);
}

int hash(const char *s){
	//generate a key for our array based off the string
	int key = 0;
  	while (*s) {
    	key = key*37 + *s++;
  	}
		if(key < 0){
			key = key * -1;
		}
	return key;
}
// remove a string from the hashtable; if the string
// doesn't exist in the hashtable, do nothing
void hashtable_remove(hashtable_t *hashtable, const char *s) {
	pthread_mutex_lock(&hashtable->globalLock);
	int key = hash(s);
	key = key % (hashtable->size);
	list_remove((list_t *)hashtable->buckets[key],s);
	pthread_mutex_unlock(&hashtable->globalLock);
}

// print the contents of the hashtable
void hashtable_print(hashtable_t *hashtable) {
	int i = 0;
	for(;i<hashtable->size;i++){
		list_print((list_t *)hashtable->buckets[i]);
	}
}


