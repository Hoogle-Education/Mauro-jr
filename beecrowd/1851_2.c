#include <stdio.h>
#include <stdlib.h>
#define breakNull(x) \
  if (x == NULL)     \
  break

typedef struct dragon
{
  int days;
  int fine;
  int arrivalTime;
  float val;
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

void heapifyUp(Heap *heap, int index)
{
  int parent = (index - 1) / 2;
  Dragon *indexDragon = &heap->dragons[index];
  Dragon *parentDragon = &heap->dragons[parent];

  if (parent >= 0 && indexDragon->val > parentDragon->val)
  {
    swap(&heap->dragons[parent], &heap->dragons[index]);
    heapifyUp(heap, parent);
  }
}

void heapifyDown(Heap *heap, int index)
{

  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;
  int greatest = index;
  Dragon *greatestDragon = &heap->dragons[greatest];

  if (leftChild < heap->size)
  {
    Dragon *leftDragon = &heap->dragons[leftChild];

    if (leftDragon->val > greatestDragon->val)
    {
      greatest = leftChild;
      greatestDragon = &heap->dragons[greatest];
    }
  }

  if (rightChild < heap->size)
  {
    Dragon *rightDragon = &heap->dragons[rightChild];

    if (rightDragon->val > greatestDragon->val)
    {
      greatest = rightChild;
      greatestDragon = &heap->dragons[greatest];
    }
  }

  if (greatest != index)
  {
    swap(&heap->dragons[index], &heap->dragons[greatest]);
    heapifyDown(heap, greatest);
  }
}

void insertDragon(Heap *heap, int days, int fine, int arrival)
{
  heap->size++;

  Dragon dg;
  dg.days = days;
  dg.fine = fine;
  dg.arrivalTime = arrival;
  dg.val = (float)fine / (float)days;
  heap->dragons = realloc(heap->dragons, heap->size * sizeof(Dragon));
  heap->dragons[heap->size - 1] = dg;

  heapifyUp(heap, heap->size - 1);
}

Dragon *extractMax(Heap *heap)
{
  if (heap->size <= 0)
  {
    printf("Heap is empty.\n");
    return NULL;
  }

  Dragon *maxDragon = &heap->dragons[0];
  heap->dragons[0] = heap->dragons[heap->size - 1];
  heap->size--;

  if (heap->size > 0)
  {
    heap->dragons = realloc(heap->dragons, heap->size * sizeof(Dragon));
    heapifyDown(heap, 0);
    return maxDragon;
  }
  else
  {
    free(heap->dragons);
    heap->dragons = NULL;
  }
}

// precisa modificar
int main()
{
  Heap heap;
  initializeHeap(&heap);

  long long int day = 0, time = 0, totalFine = 0, d, f;
  while (scanf("%lld %lld", &d, &f) != EOF)
  {
    puts("a");
    insertDragon(&heap, d, f, day);

    if (time == 0)
    {
      Dragon *dg = extractMax(&heap);
      if (dg == NULL)
        puts("sem dragao");
      totalFine += (day - dg->arrivalTime) * dg->fine;
      time = dg->days;
    }
    time--;
    day++;
    printf("A: days %d , time %d\n", day, time);
  }
  while (heap.size != 0)
  {
    if (time == 0)
    {
      Dragon *dg = extractMax(&heap);
      totalFine += (day - dg->arrivalTime) * dg->fine;
      time = dg->days;
    }

    time--;
    day++;
    printf("B: size: %d days %d , time %d\n", heap.size, day, time);
  }

  printf("%lld\n", totalFine);

  return 0;
}