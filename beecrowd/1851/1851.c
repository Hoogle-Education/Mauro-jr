#include <stdio.h>
#include <stdlib.h>

typedef long long int big_int;

typedef struct dragon
{
  int tax;
  int daysToTrain;
  int arrivalTime;
} Dragon;

typedef struct heap
{
  Dragon *dragons;
  int size;
  big_int days;
  big_int time;
  big_int payment;
} Heap;

void initializeHeap(Heap *heap)
{
  heap->dragons = NULL;
  heap->size = 0;
  heap->days = 0;
  heap->time = 0;
  heap->payment = 0;
}

void insertDragon(Heap *heap, int trainDays, int tax)
{
  heap->size++;

  Dragon dragon;
  dragon.daysToTrain = trainDays;
  dragon.tax = tax;
  dragon.arrivalTime = heap->days;
  // dragon.val = (float)tax / (float)heap->days;
  heap->dragons = realloc(heap->dragons, heap->size * sizeof(Dragon));

  heap->dragons[heap->size - 1] = dragon;

  heapifyUp(heap, heap->size - 1);
}

int comparator(Dragon *a, Dragon *b)
{
  // TODO: ver segundo criterio
  return a->arrivalTime - b->arrivalTime;
}

void swap(Dragon *a, Dragon *b)
{
  Dragon temp = *a;
  *a = *b;
  *b = temp;
}

// TODO change to max heap
void heapifyUp(Heap *heap, int index)
{
  int parent = (index - 1) / 2;
  // TODO problema com ponteiro
  int comparison = comparator(
      &heap->dragons[parent],
      &heap->dragons[index]);

  if (parent >= 0 && comparison < 0)
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

  if (leftChild < heap->size)
  {
    int leftComparison = comparator(
        &heap->dragons[leftChild],
        &heap->dragons[greatest]);

    if (leftComparison > 0)
      greatest = leftChild;
  }

  if (rightChild < heap->size)
  {
    int rightComparison = comparator(
        &heap->dragons[rightChild],
        &heap->dragons[greatest]);

    if (rightComparison > 0)
      greatest = rightChild;
  }

  if (greatest != index)
  {
    swap(&heap->dragons[index], &heap->dragons[greatest]);
    heapifyDown(heap, greatest);
  }
}

void extractMax(Heap *heap)
{
  if (heap->size <= 0)
  {
    printf("Heap is empty.\n");
    return -1;
  }

  Dragon *max = &heap->dragons[0];
  heap->dragons[0] = heap->dragons[heap->size - 1];
  heap->size--;

  if (heap->size > 0)
    heap->dragons = realloc(heap->dragons, heap->size * sizeof(int));
  else
  {
    free(heap->dragons);
    heap->dragons = NULL;
  }

  heapifyDown(heap, 0);
}

void processDragon(Dragon *dragon)
{
}

// precisa modificar
int main()
{
  Heap heap;
  initializeHeap(&heap);

  big_int day = 0, time = 0;
  big_int payment = 0, d, f;

  while (scanf("%lld %lld", &d, &f) != EOF)
  {
    insert(heap, createDragao(d, d, day));

    if (time == 0)
    {
      Dragon *dg = &heap->dragons[0];
      removeMax(heap);
      payment += (day - dg->arrivalTime) * dg->tax;
      time = dg->days;
    }

    time--;
    day++;
  }

  // TODO: achar dias restantes para passar
  while (heap.size != 0)
  {
    if (time == 0)
    {
      Dragon *dg = heap->a[0];
      removeMax(heap);
      payment += (day - dg->arrivalTime) * dg->tax;
      time = dg->days;
    }

    time--;
    day++;
  }

  printf("%lld\n", payment);

  return 0;
}