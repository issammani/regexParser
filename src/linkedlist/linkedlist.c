#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// creates an empty linked list
linkedList new_linkedList(){
    linkedList l = NULL;
    return l;
}

// adds node to the list
void add_node(linkedList* l,int data){
    node* n = malloc(sizeof(node));
    
    if(n == NULL)
        exit(1); // No memory
    
    n->data = data;
    n->next = *l;
    
    *l = n;
}

// returns 0 if not empty
int is_empty(linkedList* l){
    return *l == NULL;
}

// prints a linked list
void print(linkedList l){
    linkedList tmp = l;
    
    while(!is_empty(&tmp)){
        printf("%d \t",tmp->data);
        tmp = tmp->next;
    }
}

// frees the linked list
void free_list(linkedList l) {
    node *tmp = l;
    while (tmp) {
        l = tmp;
        tmp = tmp->next;
        free(l);
    }
}
