#ifndef POINT_H
#define POINT_H
#include "list.h"
#include <stdio.h>

typedef struct point Point;

Point *create(char *id, float *coords, int m);
char *getId(Point *p);
void printPoint(Point *p, FILE *fileOut);
void printPointDefault(Point *p);
float distance(Point *x, Point *y);
float deletePoint(Point *p);
int comparePoints(const void *a, const void *b);
void SortPointsName(List *points);

#endif