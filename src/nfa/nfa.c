#include <stdio.h>
#include <stdlib.h>
#include "../linkedlist/linkedlist.h"
#include "../digraph/digraph.h"
#include "nfa.h"

// creates an nfa : Q number of states
NFA new_nfa(int Q){
    NFA nfa;
    nfa.dg = new_diGraph(Q);
    nfa.initial_state = -1;
    nfa.to_free = malloc(sizeof(char*));
    return nfa;
}

// creates an nfa from file
NFA nfa_from_file(char* filename){

}

// returns a copy of an nfa
NFA copy_nfa(NFA nfa){
  
}

// sets the initial state
void set_initial_state(NFA *nfa,int qs){
    assert_initial(*nfa,qs);
    nfa->initial_state = qs;
}

// checks if intial state already exists
void assert_initial(NFA nfa,int qs){ 
    validate_state(nfa,qs);  
    if(nfa.initial_state != -1){
        fprintf(stderr,"[NFA] : nfa already has an initial state \n");
        exit(1);
    }
}

// checks if state is in range
void validate_state(NFA nfa, int q){
    if(q < 0 || q >= nfa.dg.V){
        fprintf(stderr,"[NFA] : state must be between 0 and %d \n",nfa.dg.V - 1);
        exit(1);
    }
}


// adds a transition between two states ('/0' for epsilon transition)
void add_transition(NFA *nfa,int q1, int q2,char symbol){

    validate_state(*nfa,q1);
    validate_state(*nfa,q2);
    char* _sym = malloc(sizeof(char));
    *_sym = symbol;
    
    // a transition is represented by an edge in the directed graph
    add_edge(&nfa->dg,q1,q2,_sym);

    // need better solution
    nfa->to_free = realloc(nfa->to_free,nfa->dg.E * sizeof(char*) );
    nfa->to_free[nfa->dg.E - 1] = _sym;

}

// prints all reachable states for every states
void print_nfa(NFA nfa){
    if(nfa.initial_state != -1)
        printf("Initial state : %d \n",nfa.initial_state);
    print_adj(nfa.dg,print_symbol);
}


static void print_symbol(void* data){
    adj_node* an = (adj_node*)data;
    int target = an->w;
    char symbol= *((char*)an->additional_data);
    
    printf("(%d,",target);
    if(symbol == epsilon)
        printf("eps) \t");
    else
        printf("%c) \t",symbol);
}


// implements the five basic NFA-fragments
NFA character_fragment(char c){
    NFA n = new_nfa(2);
    set_initial_state(&n,0);
    add_transition(&n,0,1,c);
    printf("got out ?");
    return n;
}

NFA epsilon_fragment(){
    return character_fragment(epsilon);
}

// implements concatenation operator(.)
NFA concat_fragment(NFA n1,NFA n2){
    int _size = n1.dg.V + n2.dg.V;
    NFA n = new_nfa(_size);

    linkedList *ptr = n.dg.adj;
    linkedList *n_ptr = n1.dg.adj;

    for(int i=0; i < n1.dg.V; i++,ptr++,n_ptr++){
        linkedList n_copy = copy_list(*n_ptr);
        join_list(ptr,&n_copy);
    }
    
    n_ptr = n2.dg.adj;

    // TOCHANGE : add possibility to create a graph given a start value for the id of vertices

    for(int i=0; i < n2.dg.V; i++,ptr++,n_ptr++){
        linkedList n_copy = copy_list(*n_ptr);
        
        for(int j=0; j < n_ptr->size;j++){
            void* data = get(n_copy,j);
            int * w = (int*)data;
            *w = *w + n1.dg.V;
        }
        join_list(ptr,&n_copy);
    }

    // add an epsilon transition between final state of n1 and initial state of n2
    add_transition(&n,n1.dg.V - 1,n1.dg.V,epsilon);

    
    return n;
}

NFA union_fragment(NFA n1,NFA n2){

}

NFA closure_fragment(NFA n1);


// frees an nfa
void free_nfa(NFA nfa){

    // free all allocated symbols (need a better way to do this)
    for(int i=0; i < nfa.dg.E; i++)
        free(nfa.to_free[i]);
    free(nfa.to_free);

    // free the directed graph
    free_graph(&nfa.dg);


}