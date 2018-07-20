/**
 * Implementation of a linked list in c
 * Author: Issam Mani
 */

#ifndef _LINKEDLIST
#define _LINKEDLIST


typedef struct node {
    void* data; // here node id
    struct node* next;
}node;

// linked list 
typedef struct linkedList{
    int size;
    node* head; 
} linkedList;


// creates an empty linked list
linkedList new_linkedList();

// adds node to the list
void add_node(linkedList* l,void* data);

// returns 0 if not empty
int is_empty(node* n);

//returns element at given index
void* get(linkedList l, int index);

// prints a linked list
void print(linkedList l,void (*print)(void* data));

// frees the linked list
void free_list(linkedList l);

#endif