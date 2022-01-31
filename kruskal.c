#include "kruskal.h"
#include "list.h"
#include "unionFind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *Kruskal(Graph *graph, List *subsets, int k) {
    int V = getV(graph);
    List *result = InitList(EDGE);
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Ordena tudo por ordem crescente de peso
    qsortGraph(graph);
    // PrintList(getEdges(graph), "EDGES arrumados");

    // Cria V subsets com 1 elemento
    for (int i = 0; i < V; i++)
        InsertList(subsets, createSubset(i, 0));

    // Ter apenas V-1 arestas
    while (e < V - 1 && i < getE(graph)) {

        // Pega a menor aresta da listra ordenada
        Edge *edge = GetItemList(getEdges(graph), i++);

        int x = find(subsets, getEdgeSrc(edge));
        int y = find(subsets, getEdgeDest(edge));

        // Verifica se não vai fazer um circulo
        // Ignora as k maiores arestas
        if (x != y && V - k > e) {
            InsertList(result, edge);
            Union(subsets, x, y);
            e++;
        }
    }

    return result;
}
