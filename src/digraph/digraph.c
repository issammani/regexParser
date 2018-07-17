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
    validateVertex(*dg,v);
    validateVertex(*dg,w);
    // adj[v].add(w);
    // indegree[w]++;
    // E++;
}

// returns adj list for vertex v
linkedList adj(int v);

// returns the number of directed edges incident from vertex
int outdegree(int v);

// returns the number of directed edges incident to vertex
int indegree(int v);

//returns the number of vertices
int number_of_vertices(diGraph dg){
    return dg.V;
}

//returns the number of edges
int number_of_edges(diGraph dg){
    return dg.E;
}