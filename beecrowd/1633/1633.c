#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long long int entrada;
  long long int ciclos;
} Processo;

typedef struct heap {
  Processo *processos;
  int size;
} Heap;

typedef struct {
  int size;
  int capacity;
  Processo* processos;
} Vector;

void create(Vector* vector, int size) {
  vector->processos = (Processo *) (size * sizeof(Processo));
  vector->size = 0;
  vector->capacity = size;
}

void push(Vector* vector, Processo* p) {
  if(vector->size >= vector->capacity)
    return;

  vector->processos[vector->size++] = p;
}

void merge(Processo* arr, int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  Processo* L = (Processo*)malloc(n1 * sizeof(Processo));
  Processo* R = (Processo*)malloc(n2 * sizeof(Processo));

  for (i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  i = 0; j = 0; k = left;
  while (i < n1 && j < n2) {
    if (L[i].espera <= R[j].espera) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void sort(Processo* arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // Ordena a metade esquerda
    sort(arr, left, mid);
    // Ordena a metade direita
    sort(arr, mid + 1, right);

    // Faz o merge das duas metades ordenadas
    merge(arr, left, mid, right);
  }
}

void initializeHeap(Heap *heap)
{
  heap->processos = NULL;
  heap->size = 0;
}

int comparaCiclos(Processo *p1, Processo *p2) {
  return p1->ciclos - p2->ciclos;
}

int comparaEntrada(Processo *p1, Processo *p2) {
  return p2->entrada - p1->entrada;
}

void swap(Processo *p1, Processo *p2) {
  Processo* aux = p1;
  p1 = p2;
  p2 = aux;
}

void heapifyMinHeap(Heap *h, int father) 
{
    int left, right, min;
    left = 2*father + 1; 
    right = 2*father + 2;
    min = father;

    if (right < h->size && h->processos[right].ciclos <= h->processos[min].ciclos) 
    {
        min = right;
    }

    if (left < h->size && h->processos[left].ciclos <= h->processos[min].ciclos) 
    {
        min = left;
    }

    if (min != father) 
    {
        swap(&(h->processos[father]), &(h->processos[min]));
        heapifyMinHeap(h, min);
    }
}

void inserir(Heap* heap, Processo *p) {
  if(heap->size == 1) {
    heap->processos = malloc(sizeof(Processo) * heap->size);
  } else {
    heap->processos = realloc(heap->processos, heap->size * sizeof(Processo));
  }

  heap->processos[heap->size - 1] = p;
  int father = heap->size - 1;
  while(father != 0 && (heap->processos[father].ciclos) < (heap->processos[(father-1)/2].ciclos)){
    swap(&(heap->processos[father]), &(heap->processos[(father-1)/2]));
    father = (father-1)/2;
  }
}

Processo* remover(Heap* heap) {
  if(heap->size == 0) {
    puts("Erro");
    return NULL;
  }

  Processo *p = heap->processos[0];
  heap->processos[0] = heap->processos[heap->size - 1];
  heap->size--;
  heapifyMinHeap(heap);
  return p;
}

int main() {
  int n, i;
  Processo *p, *atual;
  Heap* heap;
  Vector* processos;
  initializeHeap(heap);
  long long espera;
  long long int percorrido;

   while(scanf("%d", &n) != EOF) {
    espera = 0;
    percorrido = 0;

    long long entrada, ciclos;
    create(processos, n);
    for(int i = 0; i < n; i++) {
      scanf("%d %d", &entrada, &ciclos);
      p->ciclos = ciclos;
      p->entrada = entrada;

      if(i == 0 || entrada < percorrido ) 
        percorrido = entrada;
      
      push(processos, p);
    }

    // TODO: validar merge sort
    sort(processos);

    for(int i = 0; i < processos->size; i++) {
      Processos *p = processos->processos[i];

      if(p->entrada > percorrido) {

      }
    }

    printf("%d\n", espera);
   }

  return 0;
}