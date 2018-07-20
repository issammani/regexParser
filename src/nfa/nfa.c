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
    
    //TODO
}