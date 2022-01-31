// A union-find algorithm to detect cycle in a graph
#include "list.h"

// a structure to represent an edge in graph
typedef struct edge Edge;

// a structure to represent a graph
typedef struct graph Graph;

// A structure to represent a subset for union-find
typedef struct subset Subset;

Subset *createSubset(int parent, int rank);

Edge *createEdge(int src, int dest, float weight);

Graph *createGraph(int V, List *edges);

List *getEdges(Graph *graph);

int getV(Graph *graph);
int getE(Graph *graph);
int getEdgeSrc(Edge *edge);
float getEdgeWeight(Edge *edge);

int getEdgeDest(Edge *edge);
int find(List *subsets, int index);

void Union(List *subsets, int x, int y);
int compareEdges(const void *a, const void *b);

int getSubsetParent(Subset *subset);
int getSubsetRank(Subset *subset);

void qsortGraph(Graph *graph);
void deleteEdge(Edge *e);
void deleteSubset(Subset *s);
void DeleteGraph(Graph *g);