#include <pthread.h>
#include "list.h"

/* ************************************** 
 *
 * ************************************** */
void list_init(list_t *list) {
    list->head = NULL;
		pthread_mutex_init(&list->lock,NULL);
}


/* ************************************** 
 * print the contents of the list to file f.
 * ************************************** */
void list_print(list_t *list, FILE *f) {
		pthread_mutex_lock(&list->lock);
    printf("*** List Contents Begin ***\n");
    struct __list_node *tmp = list->head;
    while (tmp) {
        fprintf(f, "%s\n", tmp->data);
        tmp = tmp->next;
    }
    printf("*** List Contents End ***\n");
		pthread_mutex_unlock(&list->lock);
}


/* ************************************** 
 * add item "val" to the list, in order.
 * ************************************** */
void list_add(list_t *list, char *val) {
		pthread_mutex_lock(&list->lock);
    struct __list_node *new_node = (struct __list_node *)malloc (sizeof(struct __list_node));
    if (!new_node) {
        fprintf(stderr, "No memory while attempting to create a new list node!\n");
        abort();
    }

    new_node->data = val;
    new_node->next = list->head->next;

    struct __list_node *tmp = list->head;

    /* special case: list is currently empty */
    if (list->head == NULL) {
        list->head = new_node;
    }
		pthread_mutex_unlock(&list->lock);
}


/* ************************************** 
 * ************************************** */
void list_remove(list_t *list, char *target) {
		pthread_mutex_lock(&list->lock);
    /* short cut: is the list empty? */
    if (list->head == NULL){
		pthread_mutex_unlock(&list->lock);
        return;
}
    struct __list_node *tmp = list->head;
		//take care of case where head is deleted
		while(strcmp(tmp->data, target) == 0){
			list->head = tmp->next;
			//free those nodes
			//TODO
			tmp = list->head;
		}
		//take care of everything else
    while (tmp->next != NULL) {
				if(strcmp(tmp->next->data, target) == 0){
					free(tmp->next->data);
					tmp->next = tmp->next->next;
					//free node
					//TODO
				}else{
		     	tmp = tmp->next;
				}
    }

		pthread_mutex_unlock(&list->lock);
    return;
}


/* ************************************** 
 * clear out the entire list, freeing all
 * elements.
 * ************************************** */
void list_clear(list_t *list) {
		pthread_mutex_lock(&list->lock);
    struct __list_node *tmp = list->head;
    while (tmp) {
        struct __list_node *tmp2 = tmp->next;
				free(tmp->data);
        free(tmp);
        tmp = tmp2;
    }
    list->head = NULL;
		pthread_mutex_unlock(&list->lock);
		pthread_mutex_destroy(&list->lock);
}
