#ifndef _NFA
#define _NFA

#include "../digraph/digraph.h"


// NFA structure
typedef struct NFA{
    diGraph dg;
    int initial_state;
    linkedList final_states;
    char** sym_to_free;
    struct NFA* nfa_to_free;
}NFA;

// for epsilon transition
#define epsilon '\0'

// creates an nfa : Q number of states
NFA new_nfa(int Q);

// creates an nfa from file
NFA nfa_from_file(char* filename);

// returns a copy of an nfa
NFA copy_nfa(NFA nfa,int shift_by);

// adds shift value to existing states in a linkedlist
static void shift_states(linkedList *l,int shift_by);

// sets the initial state
void set_initial_state(NFA *nfa,int qs);

// adds final state to the list
void add_final_state(NFA *nfa,int qf);

// removes final state from the list
void remove_final_state(NFA *nfa,int qf);

// removes all final states from the list
void remove_all_final_states(NFA *nfa);

// returns true if state q is final
int is_final(NFA nfa,int q);

// checks if intial state already exists
void assert_initial(NFA nfa,int qs);

// checks if state is in range
void validate_state(NFA nfa, int q);

// adds a transition between two states
void add_transition(NFA *nfa,int q1, int q2,char symbol);

// prints all reachable states for every states
void print_nfa(NFA nfa);
static void print_symbol(void* data);
static void print_int(void* data);

// implements the five basic NFA-fragments
NFA character_fragment(char c);
NFA epsilon_fragment();
NFA concat_fragment(NFA n1,NFA n2);
NFA union_fragment(NFA n1,NFA n2);
NFA closure_fragment(NFA n1);

// frees an nfa
void free_nfa(NFA nfa);

#endif