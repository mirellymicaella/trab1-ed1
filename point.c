#include "point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    char *id;
    float *coords;
    int m;
};

Point *create(char *id, float *coords, int m) {
    Point *p = (Point *)malloc(sizeof(Point));

    p->id = strdup(id);
    p->coords = coords;
    p->m = m;

    return p;
}

char *getId(Point *p) { return p->id; }

void printPoint(Point *p, FILE *fileOut) {
    fprintf(fileOut, "%s : [ ", p->id);

    for (int i = 0; i < p->m; i++)
        fprintf(fileOut, "%.2f, ", p->coords[i]);

    fprintf(fileOut, "]\n");
}

void printPointDefault(Point *p) { printf("%s, ", p->id); }

float distance(Point *x, Point *y) {
    float distance = 0;
    for (int i = 0; i < x->m; i++)
        distance += pow(y->coords[i] - x->coords[i], 2);

    return sqrt(distance);
}

int comparePoints(const void *a, const void *b) {
    char *a1 = (*(Point **)a)->id;
    char *b1 = (*(Point **)b)->id;
    return strcmp(a1, b1);
}

void SortPointsName(List *points) {
    qsort(GetItems(points), GetSize(points), sizeof(Point *), comparePoints);
}

float deletePoint(Point *p) {
    free(p->coords);
    free(p->id);
    free(p);
}