#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"

// creates a new directed graph
diGraph new_diGraph(int V){
    // make sure the number of vertices is greater than 0
    if( V < 0){
        perror("new_diGraph : Number of vertices must be greater than zero.");
        exit(1);
    }
    
    diGraph dg;
    
    dg.V = V;
    dg.E =0;

    dg.indegree = malloc(V * sizeof(int));
}

// makes sure vertex is in range
void validate_vertex(int v);

// add edge between two vertices
void add_edge(int v, int w);

// returns adj list for vertex v
linkedList adj(int v);

// returns the number of directed edges incident from vertex
int outdegree(int v);

// returns the number of directed edges incident to vertex
int indegree(int v);

//returns the number of vertices
int number_of_vertices();

//returns the number of edges
int number_of_edges();