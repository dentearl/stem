struct doubleList{
   double d;
   struct doubleList *next;
};
typedef struct doubleList doubleList;

void initList(doubleList *dl);
void addToList(doubleList **dl, double data);
int countList(doubleList *dl);
void releaseList(doubleList *dl);
double * listToArray(doubleList *dl, int n);
void printList(doubleList *dl);
void memError(void);
