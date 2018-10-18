#include <stddef.h>
#include <stdio.h>
#ifndef _HEAP_SORT_H
void *heapsort(void *, size_t);
typedef long T;

#ifdef DEBUG
/* len = sizeof array / sizeof element*/
void maxHeapify(T *, size_t , size_t);
void print_arr(T *, size_t);
void buildMaxHeap(T *, size_t);
#endif

#endif 
