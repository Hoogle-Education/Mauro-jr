#include <stdio.h>
#include <stdlib.h>

typedef struct funcionario
{
  int id;
  int speed;
  int remainingTime;
} Employee;

typedef struct heap
{
  Employee *employees;
  int size;
  int tItem;
} Heap;

int comparator(Employee *a, Employee *b)
{
  if (a->remainingTime == b->remainingTime)
    return a->id - b->id;

  return a->remainingTime - b->remainingTime;
}

void initializeHeap(Heap *heap)
{
  heap->employees = NULL;
  heap->size = 0;
}

void swap(Employee *a, Employee *b)
{
  Employee temp = *a;
  *a = *b;
  *b = temp;
}

void heapifyUp(Heap *heap, int index)
{
  int parent = (index - 1) / 2;
  int comparison = comparator(
      &heap->employees[parent],
      &heap->employees[index]);

  if (parent >= 0 && comparison > 0)
  {
    swap(&heap->employees[parent], &heap->employees[index]);
    heapifyUp(heap, parent);
  }
}

void insertEmployee(Heap *heap, int id, int speed)
{
  heap->size++;

  Employee new;
  new.id = id;
  new.speed = speed;
  new.remainingTime = 0;

  heap->employees = realloc(heap->employees, heap->size * sizeof(Employee));
  heap->employees[heap->size - 1] = new;

  heapifyUp(heap, heap->size - 1);
}

void processItem(Heap *heap, int time)
{
  if (heap->size <= 0)
  {
    printf("Heap is empty.\n");
    return -1; // Indicador de erro
  }

  Employee *min = &heap->employees[0];
  min->remainingTime = min->speed * time;
  heapifyDown(heap, 0);
}

// 3 5
// 1(0) 2(0) 3(0)
// 2(0) 3(0) 1(3)
// 3(0) 2(8) 1(3)
// 3(3) 2(5) 1(0) + 3
// 1(11) 3(3) 2(5) + 3
// 3(3) 2(5) 1(11) + 3
// 3(0) 2(2) 1(8) + 3 + 3
// 3(15) 2(2) 1(8) + 3 + 3
// 2(2) 1(8) 3(15) + 3 + 3
// 2(0) 1(6) 3(13) + 3 + 3 + 2
// 1(0) 3(7) 2(0) + 3 + 3 + 2 + 6
// 3(7) 1(0) 2(0) + 3 + 3 + 2 + 6 + 7 = 21
// 3 4 2 11 5

// ordena (crescente) pelo tempo faltante
// depois, ordena (crescente) pelo id

// se o houver alguem disponivel
// escolhe o mais disponivel de menor id
// adiciona o item
// senao (liberaFuncionario)
// processa o menor tempo de processamento
// ajusta os funcionarios
// insere o novo processo no que ficou livre

// se chegou ao fim, repete o processo de liberar funcionarios
// enquanto houver algum funcionario ocupado
void heapifyDown(Heap *heap, int index)
{
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;
  int smallest = index;

  int leftComparison = comparator(
      &heap->employees[leftChild],
      &heap->employees[smallest]);

  int rightComparison = comparator(
      &heap->employees[rightChild],
      &heap->employees[smallest]);

  if (leftChild < heap->size && leftComparison < 0)
    smallest = leftChild;

  if (rightChild < heap->size && rightComparison < 0)
    smallest = rightChild;

  if (smallest != index)
  {
    swap(&heap->employees[index], &heap->employees[smallest]);
    heapifyDown(heap, smallest);
  }
}

Employee *extractMin(Heap *heap)
{
  if (heap->size <= 0)
  {
    printf("Heap is empty.\n");
    return -1; // Indicador de erro
  }

  Employee *min;
  min->id = heap->employees[0].id;
  min->speed = heap->employees[0].speed;

  heap->employees[0] = heap->employees[heap->size - 1];
  heap->size--;

  if (heap->size > 0)
    heap->employees = realloc(heap->employees, heap->size * sizeof(Employee));
  else
  {
    free(heap->employees);
    heap->employees = NULL;
  }

  heapifyDown(heap, 0);
  return min;
}

int main()
{
  Heap heap;
  initializeHeap(&heap);
  int N, M, i, j;
  scanf("%d %d", &N, &M);

  for (i = 1; i <= N; i++)
  {
    int speed;
    scanf("%d", &speed);
    insertEmployee(&heap, i, speed);
  }

  printf("Heap elements: ");

  while (heap.size > 0)
  {
    int min = extractMin(&heap);
    printf("%d, %d ", min);
  }

  return 0;
}