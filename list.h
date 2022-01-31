#ifndef LIST_H
#define LIST_H
#include <stdio.h>

#define POINT 1
#define EDGE 2
#define SUBSET 3
#define INT 4
#define LIST 5

typedef struct list List;
typedef struct celula Celula;

List *InitList(int type);

void InsertList(List *list, void *item);
void RemoveList(List *list, int index);

void PrintList(List *list, char *title);
void **GetItems(List *list);
void *GetItemList(List *list, int index);
void SetItemList(List *list, int index, void *item);
int ContainsList(List *list, void *item);
void PrintListFile(List *list, FILE *fileOut);
List *CopyList(List *list);

void DestroiList(List *list);
void FreeList(List *list);
int GetSize(List *list);
int compareLists(const void *a, const void *b);
void SortGroupsName(List *groups[], int num);
#endif