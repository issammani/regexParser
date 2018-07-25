/**
 * Implementation of a directed graph in c using adjacency list
 * Author: Issam Mani
 * this implementation was based on princeton's java implementation of
 * a directed graph
 * for more check : + https://algs4.cs.princeton.edu/42digraph/Digraph.java.html
 *                  + https://algs4.cs.princeton.edu/42digraph/DirectedDFS.java.html
 */

#ifndef _DIGRAPH
#define _DIGRAPH

#include "../linkedlist/linkedlist.h"
#include <stdbool.h>

// used as a generic placeholder for any addtional data besides the neighbor
typedef struct {
    int w; // neighbor
    void* additional_data; // cost, weight, transition character...
}adj_node;

// directed graph definition
typedef struct {
    int V; // number of vertices
    int E; // number of edges
    linkedList* adj; // adj[v] = adjacency list for vertex v
    int* indegree;   // indegree[v] = indegree of vertex v
    bool* marked; // used for the dfs
}diGraph;

// creates a new directed graph
diGraph new_diGraph(int V);

// makes sure vertex is in range
void validate_vertex(diGraph dg,int v);

// add edge between two vertices
void add_edge(diGraph* dg,int v, int w, void* value);

// returns adj list for vertex v
linkedList adj(diGraph dg,int v);

// returns the number of directed edges incident from vertex
int outdegree(diGraph dg,int v);

// returns the number of directed edges incident to vertex
int indegree(diGraph dg,int v);

//returns the number of vertices
int number_of_vertices(diGraph dg);

//returns the number of edges
int number_of_edges(diGraph dg);

void add_to_adj(diGraph* dg,int index,adj_node* an);

// prints adjacency list
void print_adj(diGraph dg,void (*adjacency_node_print)(void* an));

//computes the vertices in digraph G that are reachable from the source vertex s.
void directed_dfs(diGraph* dg, int s);

//Computes the vertices in digraph G that are connected to vertices s
void _directed_dfs(diGraph* dg, int* s,int size);

//recusively finds reachable nodes from node v
static void dfs(diGraph* dg, int v);

// frees a graph
void free_graph(diGraph* dg);

#endif