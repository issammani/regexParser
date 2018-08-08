#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// creates an empty linked list
linkedList new_linkedList(size_t data_size){
    linkedList l ;
    l.size = 0;
    l.data_size = data_size;
    l.head = NULL;
    return l;
}

// returns a copy of a linkedlist
linkedList copy_list(linkedList l){
    
    // create an empty linkedlist
    linkedList _l = new_linkedList(l.data_size);

    // allocate and copy each node
    for(int i=0; i < l.size; i++)
        add_node(&_l,get(l,i));

    return _l;

}

// adds node to the list
void add_node(linkedList* l,void* data){
    node* n = malloc(sizeof(node));
    void* _data = malloc(sizeof(l->data_size));
    memcpy(_data,data,l->data_size);
    
    if(n == NULL || _data == NULL){
        fprintf(stderr,"Memory allocation unsuccessful \n");
        exit(1); // No memory
    }

    l->size++;
    n->data = _data;
    n->next = l->head;
    
    l->head = n;
}

// returns 0 if not empty
int is_empty(node* n){
    return n == NULL;
}

//returns element at given index
void* get(linkedList l, int index){
    return get_node(l,index)->data;
}

//returns node at given index
node* get_node(linkedList l, int index){
    int counter = 0;
    int _index = (l.size - 1) - index;
    node* tmp = l.head;
    
    while(tmp){
        if(counter == _index)
            return tmp;
        tmp = tmp->next;
        counter++;
    }
    fprintf(stderr,"Given index %d is not in range [0,%d[ \n",index,l.size);
    exit(1);  
}

// removes node given an index
void remove_node(linkedList* l, int index){

    if(is_empty(l->head))
        return ;
    
    if(l->size == 1){
        l->size = 0;
        free(l->head->data);
        free(l->head);
        l->head = NULL; // otherwise the list is not regarded as empty in the rest of the code
        return ;
    }

    node * ptr = get_node(*l,index);
    if(index == l->size - 1){ // first added element (since this implementation is LIFO)
        l->head = get_node(*l,index - 1); // get next node
    }else{
        node * prev = get_node(*l,index + 1);
        prev->next = ptr->next;
    }

    l->size--;
    free(ptr->data);
    free(ptr);
}

// joins two linkedlists together
void join_list(linkedList* l1,linkedList* l2){


    if(is_empty(l1->head)){
        *l1 = *l2;
        return;
    }
    
    node* l1_last = get_node(*l1,0);
    l1->size += l2->size;
    l1_last->next = l2->head;
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
    
    node *tmp ;
    for(int i=0; i < l.size;i++){
        tmp = get_node(l,i);
        free(tmp->data);
        free(tmp);
    }
}
