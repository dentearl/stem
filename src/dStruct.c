#include <stdio.h>
#include <stdlib.h>
#include <float.h> /* for DBL_MAX */
#include "dStruct.h"

void initList(doubleList_t *dl) {
   dl = (doubleList_t *)malloc(sizeof(doubleList_t));
   if (dl == NULL)
      memError();
   dl -> d = 0.0;
   dl -> next = NULL;
}

void addToList(doubleList_t **dl, double data) {
   doubleList_t *p;
   p = (doubleList_t *)malloc(sizeof(doubleList_t));
   if (p == NULL)
      memError();
   p -> d = data;
   p -> next = *dl;
   *dl = p;
}

int countList(doubleList_t *dl) {
   doubleList_t *p = dl;
   int i = 0;
   while (p != NULL) {
      i++;
      p = p->next;
   }
   return i;
}

void releaseList(doubleList_t *dl) {
   doubleList_t *p = dl;
   doubleList_t *q = dl;
   int i = 0;
   while (p != NULL) {
      i++;
      p = p->next;
      free(q);
      q = p;
   }
}

double * listToArray(doubleList_t *dl, int n) {
   extern int sorted_flag;
   int i;
   double *a = NULL;
   double prev = DBL_MAX;
   doubleList_t *p;
   a = calloc(n, sizeof(double));
   if (a == NULL)
      memError();
   p = dl;
   if (sorted_flag) {
      /* 
         In this linked list we have everything stored in tail order, so
         if the input data were 1, 2, 3, 4, ... then the order we'd walk
         would be ..., 4, 3, 2, 1
      */
      for (i=n-1; i >= 0; i--) {
         if (p->d > prev) {
            fprintf(stderr, "Error, you used --sorted but the data does "
                    "not appear to be sorted at indices %d, %d: %f > %f\n", 
                    n - i - 1, n - i, p->d, prev);
            exit(EXIT_FAILURE);
         }
         a[i] = p->d;
         prev = p->d;
         p = p->next;
      }
   }else{
      for (i = 0; i < n ; i++) {
         a[i] = p->d;
         p = p->next;
      }
   }
   return a;
}

void printList(doubleList_t *dl) {
   if (dl != NULL) {
      printf("%lf%s", dl->d, (dl->next == NULL)?"\n":", ");
      printList(dl->next);
   }
}
