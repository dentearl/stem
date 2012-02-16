#ifndef DSTRUCT_H_
#define DSTRUCT_H_

typedef struct doubleList{
   double d;
   struct doubleList *next;
} doubleList_t;

void initList(doubleList_t *dl);
void addToList(doubleList_t **dl, double data);
int countList(doubleList_t *dl);
void releaseList(doubleList_t *dl);
double * listToArray(doubleList_t *dl, int n);
void printList(doubleList_t *dl);
void memError(void);

#endif // DSTRUCT_H_
