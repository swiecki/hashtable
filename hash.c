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
	//Return the table
     	return table;
}
int hashtable_size_calculator(int sizehint){
	//Round up to the next biggest prime number.
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
	} else {//Since we got tired of typing primes and didn't want to make this a prime generator.
		return sizehint;
	}
}
// free anything allocated by the hashtable library
void hashtable_free(hashtable_t *hashtable) {
	int i = 0;
	for(;i<=(hashtable->size);i++){
		//Clear each list in buckets.
		list_clear((list_t*)hashtable->buckets[i]);
		//Free each list in buckets.
		free(hashtable->buckets[i]);
	}
	//Free buckets and then the table itself. 
	free(hashtable->buckets);
	free(hashtable);
}

// add a new string to the hashtable
void hashtable_add(hashtable_t *hashtable, const char *s) {
	//Get the key from our hash function.
	int key = hash(s);
	//Modulo it to correspond to the number of buckets. Is modulo a verb? Whatever, it is now.
	key = key % (hashtable->size);
	//put the string into the bucket
	list_add((list_t *)hashtable->buckets[key], s);
}

int hash(const char *s){
	//generate a key for our array based off the string
	int key = 0;
  	while (*s) {
    	key = key*37 + *s++;
  	}
		if(key < 0){//We were getting wraparound and didn't want wraparound. The only thing that should wrap around is a ribbon on a present. 
			key = key * -1;
		}
	return key;
}
// remove a string from the hashtable; if the string
// doesn't exist in the hashtable, do nothing
void hashtable_remove(hashtable_t *hashtable, const char *s) {
	//Retrieve the key and then remove it from the list.
	int key = hash(s);
	key = key % (hashtable->size);
	list_remove((list_t *)hashtable->buckets[key],s);
}

// print the contents of the hashtable
void hashtable_print(hashtable_t *hashtable) {
	int i = 0;
	for(;i<hashtable->size;i++){
		//Dump the contents of each list.
		list_print((list_t *)hashtable->buckets[i]);
	}
}


