#ifndef _REGEX
#define _REGEX
#include <stdbool.h>
#include "../linkedlist/linkedlist.h"

// regex struct
typedef struct {
    char* rpn;// reverse polish notation (postfix)
}regex;



// // concat char
// #define CONCAT 8

// creates a new regex
regex* new_regex(char* s);

// inserts a . as explicit concatenation
static void format(regex* re, char* s);


// prints error message and exits
static void bad_regex(char* message);

// frees a regex
void free_regex(regex* re);


// intermediate to performing direct operations on char* (this way the code is cleaner)
typedef struct { // used instead of plain char*
    char* buff;
    int size;
    int free;
}string;

// returns a new string
static string* new_string(int initial_size);

// adds str to s
static void sappend(string* s, char c);

// returns resulting char* and frees the string*
static char* sterminate(string* s);

#endif