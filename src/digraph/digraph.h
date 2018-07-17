/**
 * Implementation of a directed graph in c using adjacency list
 * Author: Issam Mani
 * this implementation was based on princeton's java implementation of
 * a directed graph
 * for more check : https://algs4.cs.princeton.edu/42digraph/Digraph.java.html
 */

#ifndef _DIGRAPH
#define _DIGRAPH


typedef struct node {
    int data; // here node id
    struct node* next;
}node;

// linked list will be used for adjacency list
typedef node* linkedList;

// directed graph definition
typedef struct {
    int V; // number of vertices
    int E; // number of edges
    linkedList adj[]; // adj[v] = adjacency list for vertex v
    int indegree[];   // indegree[v] = indegree of vertex v
}diGraph;

#endif