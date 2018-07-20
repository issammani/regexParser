#include <stdio.h>
#include <stdlib.h>
#include "test_l.h"

// creates an empty linked list
linkedList new_linkedList(){
    linkedList l ;
    l.size = 0;
    l.head = NULL;
    return l;
}

// adds node to the list
void add_node(linkedList* l,void* data){
    node* n = malloc(sizeof(node));
    
    if(n == NULL)
        exit(1); // No memory
    l->size++;
    n->data = data;
    n->next = l->head;
    
    l->head = n;
}

// returns 0 if not empty
int is_empty(node* n){
    return n == NULL;
}

//returns element at given index
void* get(linkedList l, int index){
    
    int counter = 0;
    index = (l.size - 1) - index;
    node* tmp = l.head;
    
    while(tmp){
        if(counter == index)
            return tmp->data;
        tmp = tmp->next;
        counter++;
    }
    fprintf(stderr,"Given index %d is too big (%d) \n",index,counter);
    exit(1);
}

// prints a linked list
void print(linkedList l,void (*to_string)(void* data)){
    node* tmp = l.head;
    
    while(!is_empty(tmp)){
        to_string(tmp->data);
        tmp = tmp->next;
    }
}

// frees the linked list
void free_list(linkedList l) {
    node *tmp = l.head;
    while (tmp) {
        l.head = tmp;
        tmp = tmp->next;
        free(l.head);
    }
}
