#ifndef _NFA
#define _NFA

#include "../digraph/digraph.h"


// NFA structure
typedef struct {
    diGraph dg;
    int initial_state;
    int* final_states;
    linkedList to_free;
}NFA;

// for epsilon transition
#define epsilon '\0'

// creates an nfa : Q number of states
NFA new_nfa(int Q);

// sets the initial state
void set_initial_state(NFA *nfa,int qs);

// checks if intial state already exists
void assert_initial(NFA nfa,int qs);

// checks if state is in range
void validate_state(NFA nfa, int q);

// adds a transition between two states
void add_transition(NFA *nfa,int q1, int q2,char symbol);

// prints all reachable states for every states
void print_nfa(NFA nfa);
static void print_symbol(void* data);

// frees an nfa
void free_nfa(NFA nfa);

#endif