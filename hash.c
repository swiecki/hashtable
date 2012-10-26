#include "hash.h"


// create a new hashtable; parameter is a size hint
hashtable_t *hashtable_new(int sizehint) {
    int size = hashtable_size_calculator(sizehint);
		return NULL;
}
int hashtable_size_calculator(int sizehint){
	if(sizehint < 37){
		return 37;
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


