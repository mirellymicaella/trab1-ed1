#include "unionFind.h"
#include "list.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edge {
    int src;
    int dest;
    float weight;
};

struct graph {
    int V;       // número de vértices
    int E;       // número de arestas
    List *edges; // lista de arestas
};

struct subset {
    int parent;
    int rank;
};

Subset *createSubset(int parent, int rank) {
    Subset *subset = (Subset *)malloc(sizeof(Subset));
    subset->parent = parent;
    subset->rank = rank;
    return subset;
}

Edge *createEdge(int src, int dest, float weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->src = src;
    edge->dest = dest;
    edge->weight = weight;

    return edge;
}

Graph *createGraph(int V, List *edges) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = GetSize(edges);

    graph->edges = edges;

    return graph;
}

List *getEdges(Graph *graph) { return graph->edges; }

int getEdgeSrc(Edge *edge) { return edge->src; }

int getEdgeDest(Edge *edge) { return edge->dest; }
float getEdgeWeight(Edge *edge) { return edge->weight; }

int getV(Graph *graph) { return graph->V; }
int getE(Graph *graph) { return graph->E; }

int getSubsetParent(Subset *subset) { return subset->parent; }
int getSubsetRank(Subset *subset) { return subset->rank; }

int find(List *subsets, int index) {
    // Encontra a raiz e faz dela um pai
    int parent = ((Subset *)GetItemList(subsets, index))->parent;
    if (parent != index) ((Subset *)GetItemList(subsets, index))->parent = find(subsets, parent);

    return ((Subset *)GetItemList(subsets, index))->parent;
}

void Union(List *subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    Subset *subsetX = (Subset *)GetItemList(subsets, xroot);
    Subset *subsetY = (Subset *)GetItemList(subsets, yroot);

    // Anexa a menor classificação na raiz da maior
    if (subsetX->rank < subsetY->rank)
        subsetX->parent = yroot;
    else if (subsetX->rank > subsetY->rank)
        subsetY->parent = xroot;
    else {
        // se forem as mesma, uma é raiz
        subsetY->parent = xroot;
        subsetX->rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    float a1 = (*(Edge **)a)->weight;
    float b1 = (*(Edge **)b)->weight;

    if (a1 > b1) return 1;
    if (a1 < b1) return -1;
    return 0;
}

void qsortGraph(Graph *graph) {
    qsort(GetItems(graph->edges), graph->E, sizeof(Edge *), compareEdges);
}

void deleteEdge(Edge *e) { free(e); }
void deleteSubset(Subset *s) { free(s); }
void DeleteGraph(Graph *g) { free(g); }