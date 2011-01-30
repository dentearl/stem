/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1997-2000   Robert Gentleman, Ross Ihaka and the
 *                            R Development Core Team
 *
 *  May 2010
 *  Ported into a stand-alone bin by Dent A. Earl, dearl (a) soe ucsc edu
 *  ALL BUGS SHOULD BE REPORTED TO DENT A. EARL
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

#include <assert.h>
#include <math.h>
#include <limits.h> /* INT_MAX, LINE_MAX */
#include <stdio.h>
#include <stdlib.h> /* abs */
#include <getopt.h>

int debug_flag;
int verbose_flag;
float my_version_number = 0.1;
char *my_version_date = "4 May 2010";
char *r_version = "2.11.0 (2010-04-22)";

struct doubleList {
   double d;
   struct doubleList *next;
};
typedef struct doubleList doubleList;

void version(void){
   printf("stem version %.1lf, %s, based on R version %s.\n", my_version_number, my_version_date, r_version);
   exit(0);
}

void usage(void){
   fprintf(stderr, "USAGE: --scale [This controls the plot length.] --width [The desired width of plot.] --atom [a tolerance.]\n\n");
   exit(2);
}

void memError(void){
   fprintf(stderr, "Error, unable to allocate memory. Exiting.\n");
   exit(2);
}

void help(void){
   printf( "  R : A Computer Language for Statistical Data Analysis               \n"
           "  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka           \n"
           "  Copyright (C) 1997-2000   Robert Gentleman, Ross Ihaka and the      \n"
           "                            R Development Core Team                   \n"
           "**********************************************************************\n"
           "  Copyright (c) May 2010    Dent A. Earl, UCSC                        \n"
           "  Ported into a stand alone bin by Dent A. Earl dearl (a) soe ucsc edu\n"
           "  ALL BUGS SHOULD BE REPORTED TO DENT A. EARL, not the R dev team.    \n"
           "  http://users.soe.ucsc.edu/~dearl/                                   \n"
           "**********************************************************************\n"
           "                                                                      \n"
           "  This program is free software; you can redistribute it and/or modify\n"
           "  it under the terms of the GNU General Public License as published by\n"
           "  the Free Software Foundation; either version 2 of the License, or   \n"
           "  (at your option) any later version.                                 \n"
           "                                                                      \n"
           "  This program is distributed in the hope that it will be useful,     \n"
           "  but WITHOUT ANY WARRANTY; without even the implied warranty of      \n"
           "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       \n"
           "  GNU General Public License for more details.                        \n"
           "                                                                      \n"
           "  You should have received a copy of the GNU General Public License   \n"
           "  along with this program; if not, a copy is available at             \n"
           "  http://www.r-project.org/Licenses/                                  \n"
           "                                                                      \n"
           "  'stem' produces a stem-and-leaf plot of the values in STDIN. The    \n"
           "  parameter 'scale' can be used to expand the scale of the plot.  A   \n"
           "  value of 'scale=2' will cause the plot to be roughly twice as long  \n"
           "  as the default.                                                     \n"
           "\n"
           "  stdin: one number on each line of input, no puntuation or text.     \n"
           "  --scale: This controls the plot length.\n"
           "  --width: The desired width of plot.\n"
           "  --atom: a tolerance.\n\n"
           "  References:\n"
           "     Becker, R. A., Chambers, J. M. and Wilks, A. R. (1988) _The New S\n"
           "     Language_.  Wadsworth & Brooks/Cole.\n\n");
   exit(0);

}

void gatherOptions(int argc, char **argv, double *scale, double *width, double *atom)
{
   int c;
   while (1)
      {
         static struct option long_options[] =
            {
               {"debug", no_argument, &debug_flag, 1},
               {"verbose", no_argument, &verbose_flag, 1},
               {"help", no_argument, 0, 'h'},
               {"version", no_argument, 0, 'v'},
               /* These options don't set a flag.                 
                  We distinguish them by their indices. */
               {"scale",  required_argument, 0, 's'},
               {"width", required_argument, 0, 'w'},
               {"atom", required_argument, 0, 'a'},
               {0, 0, 0, 0}
            };
         /* getopt_long stores the option index here. */
         int option_index = 0;
         c = getopt_long(argc, argv, "s:w:a:",
                         long_options, &option_index);
         /* Detect the end of the options. */
         if (c == -1){
            break;
         }
         switch (c)
            {
            case 0:
               break;
            case 's':
               sscanf(optarg, "%lf", scale);
               break;
            case 'w':
               sscanf(optarg, "%lf", width);
               break;
            case 'a':
               sscanf(optarg, "%lf", atom);
               break;
            case 'h':
               help();
            case 'v':
               version();
            case '?':
               /* getopt_long already printed an error message. */
               break;
            default:
               abort ();
            }
      }
   if((*scale < 1) || (*width < 0 ) || (*atom < 0))
      usage();
}                

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
   if (p==NULL)
      memError();
   p -> d = data;
   p -> next = *dl;
   *dl = p;
}

void printList(doubleList *dl){
   if (dl != NULL){
      printf("%lf%s", dl->d, (dl->next == NULL)?"\n":", " );
      printList(dl->next);
   }
}

int countList(doubleList *dl){
   if (dl == NULL)
      return 0;
   else
      return (1+countList(dl->next));
}

void releaseList(doubleList *dl){
   if (dl != NULL){
      releaseList(dl->next);
      free(dl);
   }
}

double * listToArray(doubleList *dl, int n){
   int i;
   double *a = NULL;
   doubleList *p;
   a = calloc(n, sizeof(double));
   if (a == NULL)
      memError();
   p = dl;
   for(i=0; i<n; i++){
      a[i] = p->d;
      p = p->next;
   }
   return a;
}

void printArray(double *a, int n){
   int i;
   for (i=0; i<n; i++){
      printf("%lf%s", a[i], (i==(n-1)?"\n":", " ));
   }
}

int dbl_cmp(const void *a, const void *b){
   const double *da = (const double *)a;
   const double *db = (const double *)b;
   if (*da > *db)
      return 1;
   else
      if (*da < *db)
         return -1;
      else
         return 0;
}

int imin2(int x, int y){
   return (x<y) ? x : y;
}
int imax2(int x, int y){
   return (x<y) ? y : x;
}

void stem_print(int close, int dist, int ndigits){
   if ((close/10 == 0) && (dist < 0))
      printf("  %*s | ", ndigits, "-0");
   else
      printf("  %*d | ", ndigits, close/10);
}

int stem_leaf(double *x, int n, double scale, int width, double atom){
   double r, c, x1, x2;
   int mm, mu, k, i, j, hi, lo, xi;
   int ldigits, hdigits, ndigits, pdigits;
   /*R_rsort(x,n);*/
   qsort(x, n, sizeof(double), dbl_cmp);
   if(n <= 1)
      return 1;

   /*Rprintf("\n");*/
   printf("\n");
   if(x[n-1] > x[0]) {
      r = atom+(x[n-1]-x[0])/scale;
      c = pow(10.,(11.-(int)(log10(r)+10)));
      mm = imin2(2, imax2(0, (int)(r*c/25)));
      k = 3*mm + 2 - 150/(n+50);
      if ((k-1)*(k-2)*(k-5)==0)
         c *= 10.;
      /* need to ensure that x[i]*c does not integer overflow */
      x1 = fabs(x[0]); x2 = fabs(x[n-1]);
      if(x2 > x1) x1 = x2;
      while(x1*c > INT_MAX) c /= 10;
      if (k*(k-4)*(k-8)==0) mu = 5;
      if ((k-1)*(k-5)*(k-6)==0) mu = 20;
   } else {
      r = atom + fabs(x[0])/scale;
      c = pow(10.,(11.-(int)(log10(r)+10)));
      k = 2; /* not important what */
   }
    
   mu = 10;
   if (k*(k-4)*(k-8)==0) mu = 5;
   if ((k-1)*(k-5)*(k-6)==0) mu = 20;


   /* Find the print width of the stem. */

   lo = floor(x[0]  *c/mu)*mu;
   hi = floor(x[n-1]*c/mu)*mu;
   ldigits = (lo < 0) ? floor(log10(-lo))+1 : 0;
   hdigits = (hi > 0) ? floor(log10(hi))    : 0;
   ndigits = (ldigits < hdigits) ? hdigits : ldigits;

   /* Starting cell */

   if(lo < 0 && floor(x[0]*c) == lo)
      lo=lo-mu;
   hi = lo+mu;
   if(floor(x[0]*c+0.5) > hi) {
      lo = hi;
      hi = lo+mu;
   }

   /* Print out the info about the decimal place */

   pdigits= 1 - floor(log10(c)+0.5);

   /*Rprintf("  The decimal point is ");*/
   printf("  n = %d. The decimal point is ", n);
   if(pdigits == 0)
      /*Rprintf("at the |\n\n");*/
      printf("at the |\n\n");
   else
      /*Rprintf("%d digit(s) to the %s of the |\n\n",abs(pdigits),
        (pdigits > 0) ? "right" : "left");*/
      printf("%d digit(s) to the %s of the |\n\n",abs(pdigits),
              (pdigits > 0) ? "right" : "left");
   i = 0;
   do {
      if(lo < 0)
         stem_print(hi,lo,ndigits);
      else
         stem_print(lo,hi,ndigits);
      j = 0;
      do {
         if(x[i] < 0)
            xi = x[i]*c - .5;
         else
            xi = x[i]*c + .5;

         if( (hi == 0 && x[i] >= 0)||
             (lo <  0 && xi >  hi) ||
             (lo >= 0 && xi >= hi) )
            break;

         j++;
         if(j <= width-12) {
            /*Rprintf("%1d", abs(xi)%10);*/
            printf("%1d", abs(xi)%10);
         }
         i++;
      } while(i < n);
      if(j > width) {
         /*Rprintf("+%d", j-width);*/
         printf("+%d", j-width);
      }
      /*Rprintf("\n");*/
      printf("\n");
      if(i >= n)
         break;
      hi += mu;
      lo += mu;
   } while(1);
   /*Rprintf("\n");*/
   printf("\n");
   return 0;
}


int main (int argc, char **argv)
{
   double scale = 1.;
   double width = 80.;
   double atom  = 1e-8; /* 1e-8 */
   double d;
   int n;
   gatherOptions(argc, argv, &scale, &width, &atom);
   doubleList *list = NULL;
   initList(list);
   while (scanf("%lf", &d) == 1){
      addToList(&list, d);
   }
   double *array;
   n = countList(list);
   array = listToArray(list, n);
   releaseList(list);
   stem_leaf(array, n, scale, width, atom);
   free(array);
   return 0;
}
