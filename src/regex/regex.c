#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "regex.h"
#include "../linkedlist/linkedlist.h"

// creates a new regex
regex* new_regex(char* s){
    regex* re = malloc(sizeof(regex));
    format(re, s);
    return re;
}


// returns reverse polish notation of regex (backspace char is used for explicit concatenation)
// code taken from : https://github.com/Kviiri/Regextreme/blob/master/src/main/java/fi/helsinki/cs/kviiri/nfa/NfaFragment.java
// and slightly modified.
static void format(regex* re, char* s){
    // Backspace is used for concatenation
    char CONCAT = 8;
    // Union char
    char UNION = '|';
    //Escape char
    char ESCAPE = '\\';

    
    int _size = strlen(s);
    string* _s = new_string(_size);

    
    linkedList altsList   = new_linkedList(sizeof(int));
    linkedList nonOpsList = new_linkedList(sizeof(int));

    int _alts = 0;
    int _nonOps = 0;

    for(int i=0; i < _size; i++){
        switch(s[i]){

            case '\\':
                if (i + 1 == _size) 
                    bad_regex("Escape char error");
                i++;
                sappend(_s,s[i]);
                _nonOps++;
                continue;

            case '(':
                if (_nonOps > 1) {
                    _nonOps--;
                    sappend(_s,CONCAT);
                }
                //put away these variables on the stack
                int alts = _alts, nonOps = _nonOps;
                add_node(&altsList,&alts);
                add_node(&nonOpsList,&nonOps);
                _alts = 0;
                _nonOps = 0;
                continue;

            case ')'://end subexpression
                //mismatched parentheses
                if (is_empty(altsList.head)) {
                    bad_regex("Mismatched parentheses!");
                }
                //any nonops inside the subexpression will need to be concatenated
                while (--_nonOps > 0) {
                    sappend(_s,CONCAT);
                }
                //any alternations, likewise
                while (_alts > 0) {
                        sappend(_s,UNION);
                    _alts--;
                }
                //restore the values of alts and nonOps from the stacks
                int* palt = pop(&altsList),*pnop = pop(&nonOpsList);
                _alts = *palt;
                _nonOps = *pnop;
                //The parenthesized subexp is now a nonOp
                _nonOps++;
                free(palt);
                free(pnop);
                continue;

            case '|':
                //alternation
                //mismatches if there is no subexpression to alternate
                if (_nonOps == 0) {
                    bad_regex("Regex error: misplaced alternation");
                }
                //concatenate the subexpression
                while (--_nonOps > 0) {
                    sappend(_s,CONCAT);
                }
                _alts++;
                continue;

            case 8:
                //backspace is the concat operation in my postfix-regex
                //it must be automatically escaped ? (rare ?)
                sappend(_s,ESCAPE);
                sappend(_s,CONCAT);
                _nonOps++;
                continue;

            case '+':
            case '?':
            case '*':
                //these operators need a subexpression. without one, they fail
                if (_nonOps == 0) {
                    bad_regex("Lonely operand");
                }
                //they'll be appended without any extras
                sappend(_s,s[i]);
                continue;
        }

        //we came here for literals (or escaped characters)
        //previous subexpression? concat it
        if (_nonOps > 1) {
            _nonOps--;
            sappend(_s,CONCAT);
        }
        //finally, append the literal
        sappend(_s,s[i]);
        //it's now a new subexpression
        _nonOps++;

    }

    //finally, we concat all remaining subexpressions
    while (--_nonOps > 0) {
        sappend(_s,CONCAT);
    }

    //and append the remaining alternations
    while (_alts > 0) {
        sappend(_s,UNION);
        _alts--;
    }
    

    free_list(altsList);
    free_list(nonOpsList);

    // terminate string
    re->rpn = sterminate(_s);
}

static void bad_regex(char* message){
    fprintf(stderr,"[RegexError] : %s \n",message);
    exit(1);
}



// frees a regex
void free_regex(regex* re){
    //free_list(re->to_free);
    free(re->rpn);
    free(re);
}


// returns a new string
static string* new_string(int initial_size){
    string* s = malloc(sizeof(string));
    s->buff = malloc(initial_size);
    s->size = initial_size;
    s->free = initial_size;
    return s;
}

// adds str to s
static void sappend(string* s, char c){
    if(s->free - 1 < 0){ // not enough memory for the whole string
        s->buff = realloc(s->buff,s->size + 2);
        s->size += 2;
        s->free += 2; 
    }
    
    s->buff[s->size - s->free] = c;
    s->free--;
}

// returns resulting char* 
static char* sterminate(string* s){
    char* _s;
    int size = 0;
    if(!s->free){ // string full
        size = s->size + 1;
        _s = malloc(size);
    }else{// string has empty spaces
        size = s->size - s->free + 1;
        _s = malloc(size);
    }
    
    
    strcpy(_s,s->buff); // when s->buff has more chars will return just appropriate size
    _s[size] = '\0';
    
    free(s->buff);
    free(s);

    return _s;
}