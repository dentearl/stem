#include <stdio.h>
#include <stdlib.h>
#include "dStruct.h"

void initList(doubleList *dl){
   dl = (doubleList *)malloc(sizeof(doubleList));
   if (dl == NULL)
      memError();
   dl -> d = 0.0;
   dl -> next = NULL;
}

void addToList(doubleList **dl, double data){
   doubleList *p;
   p = (doubleList *)malloc(sizeof(doubleList));
   if (p == NULL)
      memError();
   p -> d = data;
   p -> next = *dl;
   *dl = p;
}

int countList(doubleList *dl){
   doubleList *p = dl;
   int i = 0;
   while( p != NULL ){
      i++;
      p = p->next;
   }
   return i;
}

void releaseList(doubleList *dl){
   doubleList *p = dl;
   doubleList *q = dl;
   int i = 0;
   while(p != NULL){
      i++;
      p = p->next;
      free(q);
      q = p;
   }
}

double * listToArray(doubleList *dl, int n){
   int i;
   double *a = NULL;
   doubleList *p;
   a = calloc(n, sizeof(double));
   if ( a == NULL )
      memError();
   p = dl;
   for( i=0; i < n; i++ ){
      a[i] = p->d;
      p = p->next;
   }
   return a;
}

void printList(doubleList *dl){
   if (dl != NULL){
      printf("%lf%s", dl->d, (dl->next == NULL)?"\n":", " );
      printList(dl->next);
   }
}
