#include <stdio.h>
#include <stdlib.h>

typedef struct dragon
{
  double val;
  int arrival, tax, daysUntil;
} Dragon;

typedef struct heap
{
  Dragon *dragons;
  int size;
} Heap;

void initializeHeap(Heap *heap)
{
  heap->dragons = NULL;
  heap->size = 0;
}

void swap(Dragon *a, Dragon *b)
{
  Dragon temp = *a;
  *a = *b;
  *b = temp;
}

void heapifyMinHeap(Heap *h, int father) 
{
    int left, right, min;
    left = 2*father + 1; 
    right = 2*father + 2;
    min = father;

    if (right < h->size && h->dragons[right].val <= h->dragons[min].val) 
    {
        min = right;
    }

    if (left < h->size && h->dragons[left].val <= h->dragons[min].val) 
    {
        min = left;
    }

    if (min != father) 
    {
        swap(&(h->dragons[father]), &(h->dragons[min]));
        heapifyMinHeap(h, min);
    }
}

void insertDragon(Heap *heap, int days, int t, int a)
{
  heap->size++;

  Dragon dg;
  dg.daysUntil = days;
  dg.tax = t;
  dg.arrival = a;
  dg.val = (double)days / (double)t;

  if(heap->size == 1)
  {
    heap->dragons = malloc(sizeof(Dragon) * heap->size);
  } else
  {
    heap->dragons = realloc(heap->dragons, heap->size * sizeof(Dragon));
  }
  heap->dragons[heap->size - 1] = dg;
  int father = heap->size - 1;
  while(father != 0 && (heap->dragons[father].val) < (heap->dragons[(father-1)/2].val)){
    swap(&(heap->dragons[father]), &(heap->dragons[(father-1)/2]));
    father = (father-1)/2;
  }
}

void extractMin(Heap *heap) {
    Dragon min = heap->dragons[0];

    heap->dragons[0] = heap->dragons[heap->size - 1];
    heap->size--;

    if (heap->size > 0)
        heap->dragons = realloc(heap->dragons, heap->size * sizeof(Dragon));
    else 
    {
        free(heap->dragons);
        heap->dragons = NULL;
        return;
    }

    heapifyMinHeap(heap, 0);
}

int main()
{
  Heap heap;
  initializeHeap(&heap);
  long long int day = 0, time = 0, totalTax = 0;
  int d, t, i;

  while(scanf("%d%d", &d, &t) != EOF)
  {
  insertDragon(&heap, d, t, day);

  if(time == 0)
  {
    Dragon dg = heap.dragons[0];
    extractMin(&heap);
    totalTax += (day - dg.arrival) * dg.tax;

    time = dg.daysUntil;
  }
  time--;
  day++;
  }

  while(heap.size != 0)
  {
  if(time == 0)
  {
  Dragon dg = heap.dragons[0];
  extractMin(&heap);
  totalTax += (day - dg.arrival) * dg.tax;
  time = dg.daysUntil;
  }
  time--;
  day++;
  }

  printf("%lld\n", totalTax);

  return 0;
}