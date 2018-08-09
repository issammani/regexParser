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
    nfa.final_states = new_linkedList(sizeof(int));
    nfa.sym_to_free = malloc(sizeof(char*));
    nfa.nfa_to_free = NULL;
    return nfa;
}

// creates an nfa from file
NFA nfa_from_file(char* filename){

}

// returns a copy of an nfa
NFA copy_nfa(NFA nfa,int shift_by){

    NFA _nfa = new_nfa(nfa.dg.V);

    free_graph(&_nfa.dg); // TOFIX
    _nfa.dg = copy_graph(nfa.dg);
    
    // set initial and final states
    _nfa.initial_state = nfa.initial_state;
    _nfa.final_states = copy_list(nfa.final_states);
    shift_states(&_nfa.final_states,shift_by);

    linkedList* ptr = _nfa.dg.adj;
    for(int i=0; i < _nfa.dg.V;i++,ptr++)
        shift_states(ptr,shift_by);

    return _nfa;

}

// adds shift value to existing states in a linkedlist
static void shift_states(linkedList *l,int shift_by){
    // only if shift_by is greater than zero : assuming the id must always be 0 or greater no negatives
    if(shift_by != 0)
        for(int i=0; i < l->size;i++){
            void* data = get(*l,i);
            int* w = (int*) data;
            *w += shift_by;
        }
}

// sets the initial state
void set_initial_state(NFA *nfa,int qs){
    assert_initial(*nfa,qs);
    nfa->initial_state = qs;
}

// adds final state to the list
void add_final_state(NFA *nfa,int qf){
    validate_state(*nfa,qf);
    add_node(&nfa->final_states,&qf);
}

// removes final state from the list
void remove_final_state(NFA *nfa,int qf){
    int index = is_final(*nfa,qf);
    
    if(index == -1)
        return ; // probably should throw some error
    
    remove_node(&nfa->final_states,index);
}

// removes all final states from the list
void remove_all_final_states(NFA *nfa){
    while(nfa->final_states.size != 0)
        remove_node(&nfa->final_states,nfa->final_states.size - 1);
}

// returns index of state if state q is final otherwise -1
int is_final(NFA nfa,int q){
    validate_state(nfa,q);
    for(int i=0; i < nfa.final_states.size;i++)
        if( *(int*)get(nfa.final_states,i) == q)
            return i;
    return -1;
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
    nfa->sym_to_free = realloc(nfa->sym_to_free,nfa->dg.E * sizeof(char*) );
    nfa->sym_to_free[nfa->dg.E - 1] = _sym;

}

// prints all reachable states for every states
void print_nfa(NFA nfa){
    printf("Initial state : ");
    if(nfa.initial_state == -1)
        printf("not set \n");
    else
        printf("%d \n",nfa.initial_state);
    
    printf("Final states : ");
    if(is_empty(nfa.final_states.head))
        printf("none \n");
    else{
        print(nfa.final_states,print_int);
        printf("\n");
    }
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

static void print_int(void* data){
    printf("%d \t", *((int*) data));
}

// implements the five basic NFA-fragments
NFA character_fragment(char c){
    NFA n = new_nfa(2);
    set_initial_state(&n,0);
    add_final_state(&n,1);
    add_transition(&n,0,1,c);
    return n;
}

NFA epsilon_fragment(){
    return character_fragment(epsilon);
}

// implements concatenation operator(.)
NFA concat_fragment(NFA n1,NFA n2){
    int _size = n1.dg.V + n2.dg.V;
    
    NFA n = new_nfa(_size);
    
    set_initial_state(&n,0);
    add_final_state(&n,_size - 1);

    n.nfa_to_free = malloc(sizeof(NFA)*2);
    NFA _n1 = copy_nfa(n1,0);
    NFA _n2 = copy_nfa(n2,n1.dg.V);

    // remove all final states
    remove_all_final_states(&_n1);
    remove_all_final_states(&_n2);
    
    linkedList *ptr = n.dg.adj;
    linkedList *n_ptr = _n1.dg.adj;
    
    for(int i=0; i < _size; i++,ptr++,n_ptr++){
        if(i == _n1.dg.V)
            n_ptr = _n2.dg.adj;
        join_list(ptr,n_ptr);
    }
    // add an epsilon transition between final state of n1 and initial state of n2
    add_transition(&n,n1.dg.V - 1,n1.dg.V,epsilon);

    // keep track of the newly created nfas to free later
    n.nfa_to_free[0] = _n1;
    n.nfa_to_free[1] = _n2;

    return n;
}

NFA union_fragment(NFA n1,NFA n2){
    int _size = n1.dg.V + n2.dg.V + 2;
    
    NFA n = new_nfa(_size);
    
    set_initial_state(&n,0);
    add_final_state(&n,_size - 1);

    n.nfa_to_free = malloc(sizeof(NFA)*2);
    NFA _n1 = copy_nfa(n1,1);
    NFA _n2 = copy_nfa(n2,n1.dg.V + 1);

    // remove all final states
    remove_all_final_states(&_n1);
    remove_all_final_states(&_n2);

    linkedList *ptr = n.dg.adj + 1;
    linkedList *n_ptr = _n1.dg.adj;
    
    for(int i=1; i < _size - 1; i++,ptr++,n_ptr++){
        if(i == _n1.dg.V + 1)
            n_ptr = _n2.dg.adj;
        join_list(ptr,n_ptr);
    }

    // add first and last transitions
    add_transition(&n,0,1,epsilon);//initial_state --> _n1
    add_transition(&n,0,n1.dg.V + 1,epsilon);//initial_state --> _n2
    add_transition(&n,n1.dg.V,_size - 1,epsilon);//final_state_n1 --> final_state_n
    add_transition(&n,_size - 2,_size - 1,epsilon);//final_state_n2 --> final_state_n

    // keep track of the newly created nfas to free later
    n.nfa_to_free[0] = _n1;
    n.nfa_to_free[1] = _n2;

    return n;
}

// Kleene closure fragement (*)
NFA closure_fragment(NFA n1){
    int _size = n1.dg.V + 2;
    
    NFA n = new_nfa(_size);
    
    set_initial_state(&n,0);
    add_final_state(&n,_size - 1);

    n.nfa_to_free = malloc(sizeof(NFA));
    NFA _n1 = copy_nfa(n1,1);

    // remove all final states
    remove_all_final_states(&_n1);

    linkedList *ptr = n.dg.adj + 1;
    linkedList *n_ptr = _n1.dg.adj;
    
    for(int i=1; i <= n1.dg.V; i++,ptr++,n_ptr++){
        join_list(ptr,n_ptr);
    }

    // add first and last transitions
    add_transition(&n,0,1,epsilon);//initial_state_n --> _n1
    add_transition(&n,0,_size - 1,epsilon);//initial_state_n --> final_state_n
    add_transition(&n,n1.dg.V,_size - 1,epsilon);//final_state_n1 --> final_state_n
    add_transition(&n,_size - 1,1,epsilon);//final_state_n --> initial_state_n1

    // keep track of the newly created nfas to free later
    n.nfa_to_free[0] = _n1;

    return n;
}


// frees an nfa
void free_nfa(NFA nfa){

    // free all allocated symbols (need a better way to do this)
    for(int i=0; i < nfa.dg.E; i++)
        free(nfa.sym_to_free[i]);
    free(nfa.sym_to_free);

    if(nfa.nfa_to_free){
        // free all allocated nfa copys (need a better way to do this)
        free_nfa(nfa.nfa_to_free[0]);
        free_nfa(nfa.nfa_to_free[1]); // TOFIX : kleene star has only one nfa 
    
        free(nfa.nfa_to_free);
    }

    // free list of final states
    free_list(nfa.final_states);

    // free the directed graph
    free_graph(&nfa.dg);


}
