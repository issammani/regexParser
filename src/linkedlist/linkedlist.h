/**
 * Implementation of a linked list in c
 * Author: Issam Mani
 */

#ifndef _LINKEDLIST
#define _LINKEDLIST


typedef struct node {
    void* data; 
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

//returns node at given index
node* get_node(linkedList l, int index);

// joins two linkedlist together
void join_list(linkedList* l1,linkedList* l2);

// prints a linked list
void print(linkedList l,void (*print)(void* data));

// frees the linked list
void free_list(linkedList l);

#endif