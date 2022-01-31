#include "list.h"
#include "point.h"
#include "unionFind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    void **items;
    int size;
    int type;
};

List *InitList(int type) {
    List *list = (List *)malloc(sizeof(List));
    list->items = (void **)malloc(sizeof(void *));
    list->type = type;
    list->size = 0;
    return list;
}

void InsertList(List *list, void *item) {
    void **temp = list->items;
    int i;

    temp = realloc(temp, (list->size + 1) * sizeof(void *)); /* realloc first */
    if (temp != NULL) {
        list->items = temp;
    } else {
        fputs("realloc failed", stderr);
        free(temp); /* Free the previously malloc-ed memory */
        exit(-1);   /* Exit the program */
    }
    list->items[list->size] = item;
    list->size++;
}

void RemoveList(List *list, int index) {

    List *temp = InitList(list->type);

    // Move todos os itensa partir do index para uma casa atrás até a posição do index
    for (int i = index; i < list->size; i++)
        list->items[i] = list->items[i + 1];

    list->size--;
    free(list->items[list->size]);

    // Insere todos os items da lista principal para a temnporária
    for (int i = 0; i < list->size; i++)
        InsertList(temp, list->items[i]);

    // Realoca a lista para retirar uma posição ( a ultima )
    void **voidPointer = (void **)realloc(temp->items, temp->size * sizeof(void *));

    if (voidPointer == NULL) {
        printf("Unable to reallocate memory, exiting.\n");
        free(voidPointer);
        exit(0);
    }
    list->items = voidPointer;
}

int ContainsList(List *list, void *item) {
    for (int i = 0; i < list->size; i++)
        if (list->items[i] == item) return 1;
    return 0;
}

List *CopyList(List *list) {
    List *copy = InitList(list->type);

    for (int i = 0; i < list->size; i++)
        InsertList(copy, list->items[i]);
    return copy;
}
static void PrintBreak(int size, int *aux) {
    if ((*aux) - 1 == (size / 10)) {
        printf("\n");
        (*aux) = 0;
    }
    (*aux)++;
}

void PrintList(List *list, char *title) {
    int aux = 0;
    printf("------ %s ------\n", title);

    for (int i = 0; i < list->size; i++) {
        // PrintBreak(GetSize(list), &aux);

        if (list->type == POINT) {
            printPointDefault(list->items[i]);
        } else if (list->type == EDGE)
            printf("( %d -- %d ) \n", getEdgeSrc(list->items[i]), getEdgeDest(list->items[i]));
        else if (list->type == INT)
            printf("%d, ", *((int *)list->items[i]));
        else if (list->type == SUBSET)
            printf("(p: %d) (r: %d) \n", getSubsetParent(GetItemList(list, i)),
                   getSubsetRank(GetItemList(list, i)));
    }
    printf("\n------------------------\n");
}

void PrintListFile(List *list, FILE *fileOut) {

    if (!list) return;
    for (int i = 0; i < list->size; i++) {
        if (i == 0)
            fprintf(fileOut, "%s", getId((Point *)list->items[i]));
        else
            fprintf(fileOut, ",%s", getId((Point *)list->items[i]));
    }
    if (!list->size) return;

    if (list->items[0]) fprintf(fileOut, "\n");
}

void **GetItems(List *list) { return list->items; }

void *GetItemList(List *list, int index) { return list->items[index]; }
void SetItemList(List *list, int index, void *item) { list->items[index] = item; }

int GetSize(List *list) { return list->size; }

void DestroiList(List *list) {
    for (int i = 0; i < list->size; i++)
        if (list->items[i])
            if (list->type == POINT)
                deletePoint(list->items[i]);
            else if (list->type == SUBSET)
                deleteSubset(list->items[i]);
            else if (list->type == EDGE)
                deleteEdge(list->items[i]);
            else if (list->type == LIST)
                DestroiList(list);
    free(list->items);
    free(list);
}

void FreeList(List *list) {

    free(list->items);
    free(list);
}

int compareLists(const void *a, const void *b) {
    List *aa = *(List **)a;
    List *bb = *(List **)b;

    if (!aa->size && !bb->size) return 0;
    if (aa->size && !bb->size) return -1;
    if (!aa->size && bb->size) return 1;

    Point *a1 = (*(List **)a)->items[0];
    Point *b1 = (*(List **)b)->items[0];

    return strcmp(getId(a1), getId(b1));
}
void SortGroupsName(List *groups[], int num) { qsort(groups, num, sizeof(List *), compareLists); }