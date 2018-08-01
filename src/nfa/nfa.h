#ifndef _NFA
#define _NFA

#include "../digraph/digraph.h"


// NFA structure
typedef struct {
    diGraph dg;
    int initial_state;
    int* final_states;
    char** to_free;
}NFA;

// for epsilon transition
#define epsilon '\0'

// creates an nfa : Q number of states
NFA new_nfa(int Q);

// creates an nfa from file
NFA nfa_from_file(char* filename);

// returns a copy of an nfa
NFA copy_nfa(NFA nfa);

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

// implements the five basic NFA-fragments
NFA character_fragment(char c);
NFA epsilon_fragment();
NFA concat_fragment(NFA n1,NFA n2);
NFA union_fragment(NFA n1,NFA n2);
NFA closure_fragment(NFA n1);

// frees an nfa
void free_nfa(NFA nfa);

#endif