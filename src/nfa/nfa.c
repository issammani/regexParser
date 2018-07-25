#include <stdio.h>
#include <stdlib.h>
#include "../digraph/digraph.h"
#include "nfa.h"

// creates an nfa : Q number of states
NFA new_nfa(int Q){
    NFA nfa;
    nfa.dg = new_diGraph(Q);
    nfa.initial_state = -1;

    return nfa;
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
    printf("(%d,%c) \t",target,symbol);
}