#ifndef __HASH_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include "list.h"

typedef struct {
	struct list_t **buckets;
	int size;
	pthread_mutex_t globalLock;
} hashtable_t;

// create a new hashtable; parameter is a size hint
hashtable_t *hashtable_new(int);

//Calculate the number of buckets for the hashtable
int hashtable_size_calculator(int);

// free anything allocated by the hashtable library
void hashtable_free(hashtable_t *);

// add a new string to the hashtable
void hashtable_add(hashtable_t *, const char *);

//Generates a key for a string
int hash(const char *);

// remove a string from the hashtable; if the string
// doesn't exist in the hashtable, do nothing
void hashtable_remove(hashtable_t *, const char *);

// print the contents of the hashtable
void hashtable_print(hashtable_t *);

#endif

