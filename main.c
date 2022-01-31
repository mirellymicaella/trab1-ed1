#include "kruskal.h"
#include "list.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDistancesMatrix(float **distances, List *points) {
    int numPoints = GetSize(points);

    for (int i = 0; i < numPoints; i++) {
        printf("%s |", getId(GetItemList(points, i)));

        for (int j = 0; j < numPoints; j++)
            if (j >= i)
                printf(" ");
            else
                printf("%.2f     ", distances[i][j]);

        printf("\n");
    }
}

void PrintEdges(List *points, List *edges) {
    Edge *edge;
    for (int i = 0; i < GetSize(edges); ++i) {
        edge = (Edge *)GetItemList(edges, i);
        printf("%s -- %s == %.2f\n", getId(GetItemList(points, getEdgeSrc(edge))),
               getId(GetItemList(points, getEdgeDest(edge))), getEdgeWeight(edge));
    }
}

int GetMinimumCost(List *edges) {
    int minimumCost = 0;
    for (int i = 0; i < GetSize(edges); ++i)
        minimumCost += getEdgeWeight((Edge *)GetItemList(edges, i));
    return minimumCost;
}

float **getDistanceMatrix(List *points) {
    int numPoints = GetSize(points);
    float **distances = (float **)malloc(numPoints * sizeof(float *));
    for (int i = 0; i < numPoints; i++) {
        distances[i] = (float *)malloc(numPoints * sizeof(float));
        for (int j = 0; j < numPoints; j++)
            distances[i][j] = distance(GetItemList(points, i), GetItemList(points, j));
    }
    return distances;
}

List *GetPointsList(FILE *fileIn) {
    size_t len = 300;
    char *line = malloc(len);

    int m = 0;

    char *id;
    float *coords;
    char *item;
    char token[] = ",";

    List *points = InitList(POINT);
    int i = 0;
    // Enquanto ha linhas no arquivo de entrada
    while (getline(&line, &len, fileIn) > 0) {
        m = 0;         // Reseta a dimensao
        coords = NULL; // Reseta coordenadas

        item = strtok(line, token);
        id = item;

        item = strtok(NULL, token);
        while (item != NULL) {
            m++; // Aumenta a dimensao

            // Adiciona mais um coordenada
            coords = (float *)realloc(coords, sizeof(float) * m);
            coords[m - 1] = atof(item);

            item = strtok(NULL, token);
        };
        InsertList(points, create(id, coords, m));
    }
    free(line);

    return points;
}

void FreeDistances(float **distances, int numPoints) {
    for (int i = 0; i < numPoints; i++)
        free(distances[i]);

    free(distances);
}

int main(int argc, char const *argv[]) {
    // Verifica se todas as infos foram dadas
    if (argc < 3) {
        printf("ERRO: Informações insuficientes.\n");
        return 0;
    }

    FILE *fileIn = fopen(argv[1], "r");
    FILE *fileOut = fopen(argv[3], "w");

    // Verifica se o arquivo digitado eh um endereco valido
    if (fileIn == NULL) {
        printf("Não foi possivel encontrar o arquivo %s \n", argv[1]);
        return 0;
    }
    // Verifica se o arquivo de said foi gerado corretamente
    if (fileOut == NULL) {
        printf("Não foi possivel criar o arquivo %s \n", argv[3]);
        return 0;
    }
    // Converte k para int
    int k = atoi(argv[2]);

    List *points = GetPointsList(fileIn);
    int numPoints = GetSize(points);
    SortPointsName(points);
    float **distances = getDistanceMatrix(points);

    // cria as arestas de acordo com as distancias
    List *edges = InitList(EDGE);
    for (int i = 0; i < numPoints; i++)
        for (int j = 0; j < numPoints; j++)
            if (j > i) InsertList(edges, createEdge(i, j, distances[i][j]));

    Graph *graph = createGraph(numPoints, edges);
    List *subsets = InitList(SUBSET);
    List *result = Kruskal(graph, subsets, k);

    List *groups[numPoints];
    int group = 0;

    // inicaliza a lista de grupos
    for (int i = 0; i < numPoints; i++) {
        groups[i] = InitList(POINT);
    }

    // Monta os grupos de acordo com os pais de cada um
    // identificados pelo 'parente' de cada subset
    for (int i = 0; i < numPoints; i++) {
        Subset *subset = (Subset *)GetItemList(subsets, i);
        Point *p = (Point *)GetItemList(points, i);
        InsertList(groups[getSubsetParent(subset)], p);
    }

    SortGroupsName(groups, numPoints);

    // Imprime os grupos e libera a memória alocada para cada grupo
    for (int i = 0; i < numPoints; i++) {
        PrintListFile(groups[i], fileOut);
        FreeList(groups[i]);
    }

    // Libera todas estruturas alocadas
    DeleteGraph(graph);
    DestroiList(edges);
    FreeList(result);
    DestroiList(points);
    DestroiList(subsets);
    FreeDistances(distances, numPoints);
    fclose(fileIn);
    fclose(fileOut);

    return 0;
}
