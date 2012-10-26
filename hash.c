#include "hash.h"


// create a new hashtable; parameter is a size hint
hashtable_t *hashtable_new(int sizehint) {
    return NULL;
}

// free anything allocated by the hashtable library
void hashtable_free(hashtable_t *hashtable) {

}

// add a new string to the hashtable
void hashtable_add(hashtable_t *hashtable, const char *s) {

	//generate a key for our array based off the string
	int key = 0;
  	while (*s) {
    	key = key*37 + *s++;
  	}
	key = key % hashtable->size;
	//put the string into the bucket

}

// remove a string from the hashtable; if the string
// doesn't exist in the hashtable, do nothing
void hashtable_remove(hashtable_t *hashtable, const char *s) {

}

// print the contents of the hashtable
void hashtable_print(hashtable_t *hashtable) {

}


