#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    linkedList *ptr = dg.adj;
    for(int i=0; i < V ;i++, ptr++)
        *ptr = new_linkedList();

    // allocate memory for marked
    dg.marked = malloc(dg.V * sizeof(bool));

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
void add_edge(diGraph* dg,int v, int w,void* value){
    validate_vertex(*dg,v);
    validate_vertex(*dg,w);
    
    adj_node* an = malloc(sizeof(adj_node));
    an->w = w;
    an->additional_data = value;
    add_to_adj(dg,v,an);
    dg->indegree[w]++;
    dg->E++;
}

void add_to_adj(diGraph* dg,int index,adj_node* an){
    linkedList* tmp = dg->adj;
    for(int i = 0; i < index; i++,tmp++);
    add_node(tmp,an);
}


// prints adjacency list
void print_adj(diGraph dg,void (*adjacency_node_print)(void* an)){
    
    linkedList* tmp = dg.adj;
    for(int i =0 ; i < dg.V; i++,tmp++){
        printf("%d -->   ",i);
        print(*tmp,adjacency_node_print);
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

//computes the vertices in digraph G that are reachable from the source vertex s.
void directed_dfs(diGraph* dg, int s){
    
    validate_vertex(*dg,s);
    
    for(int i =0; i < dg->V;i++) dg->marked[i] = false; // tochange : find a better and faster way to do this
    
    dfs(dg,s);

}


//Computes the vertices in digraph G that are connected to vertices s
void _directed_dfs(diGraph* dg, int* s, int size){
    
    
    // check if all sources exist
    for(int i=0; i < size; i++)
        validate_vertex(*dg,s[i]);
    
    for(int i =0; i < dg->V;i++) dg->marked[i] = false; // tochange : find a better and faster way to do this

    for (int i=0; i < size ;i++)
            if (!dg->marked[s[i]]) dfs(dg, s[i]);

}

//recusively finds reachable nodes from node v
static void dfs(diGraph* dg, int v){
    dg->marked[v] = true;
    linkedList neighbors = adj(*dg,v);

    for (int i=0; i < neighbors.size ;i++){
        int current_neighbor = ( (adj_node*) get(neighbors,i) )->w;
        if (!dg->marked[current_neighbor]) dfs(dg, current_neighbor);
    }
            
}

// frees a graph
void free_graph(diGraph* dg){

    // free the adjecency list
    for(int i=0; i < dg->V;i++)
        free_list(adj(*dg,i));
    
    free(dg->adj);

    // free indegree 
    free(dg->indegree);

    // free marked array
    free(dg->marked);
}



