#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"
#include "../linkedlist/linkedlist.h"

// creates a new directed graph
diGraph new_diGraph(int V){
    // make sure the number of vertices is greater than 0
    if( V < 0){
        fprintf(stderr,"new_diGraph : Number of vertices must be greater than zero.\n");
        exit(1);
    }
    
    diGraph dg;
    
    dg.V = V;
    dg.E =0;

    dg.indegree = malloc(V * sizeof(int));
    dg.adj = malloc(V * sizeof(linkedList));

    return dg;
}

// makes sure vertex is in range
void validate_vertex(diGraph dg,int v){
    if(v < 0 || v >= dg.V){
        fprintf(stderr, "Vertex must be between 0 and %d\n",dg.V - 1);
        exit(1);
    }
}

// add edge between two vertices
void add_edge(diGraph* dg,int v, int w){
    validate_vertex(*dg,v);
    validate_vertex(*dg,w);
    
    add_to_adj(dg,v,w);
    dg->indegree[w]++;
    dg->E++;
}

void add_to_adj(diGraph* dg,int index,int value){
    linkedList* tmp = dg->adj;
    for(int i = 0; i < index; i++,tmp++);
    add_node(tmp,value);
}

// prints adjacency list
void print_adj(diGraph dg){
    
    linkedList* tmp = dg.adj;
    for(int i =0 ; i < dg.V; i++,tmp++){
        printf("%d -->   ",i);
        print(*tmp);
        printf("\n");
    }
}
// returns adj list for vertex v
linkedList adj(diGraph dg,int v){
    validate_vertex(dg,v);
    linkedList* tmp = dg.adj;
    for(int i=0; i < v;i++,tmp++);
    return *tmp;
}

// returns the number of directed edges incident from vertex
int outdegree(diGraph dg,int v){
    validate_vertex(dg,v);
    return adj(dg,v).size;
    
}

// returns the number of directed edges incident to vertex
int indegree(diGraph dg,int v){
    validate_vertex(dg,v);
    return dg.indegree[v];
}

//returns the number of vertices
int number_of_vertices(diGraph dg){
    return dg.V;
}

//returns the number of edges
int number_of_edges(diGraph dg){
    return dg.E;
}