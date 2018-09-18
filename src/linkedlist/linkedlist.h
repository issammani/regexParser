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
    size_t data_size;
    node* head; 
} linkedList;


// creates an empty linked list
linkedList new_linkedList(size_t data_size);

// returns a copy of a linkedlist
linkedList copy_list(linkedList l);

// adds node to the list
void add_node(linkedList* l,void* data);

// returns 0 if not empty
int is_empty(node* n);

//returns element at given index
void* get(linkedList l, int index);

//returns node at given index
node* get_node(linkedList l, int index);

// removes node given an index
void remove_node(linkedList* l, int index);

// removes node given an index
void* pop(linkedList* l);

// joins two linkedlist together
void join_list(linkedList* l1,linkedList* l2);

// prints a linked list
void print(linkedList l,void (*print)(void* data));

// frees the linked list
void free_list(linkedList l);

#endif