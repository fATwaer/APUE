#include "heapsort.h"

static size_t
_parent(size_t i)
{
    return (i / 2);
}

static size_t
_left(size_t i)
{
    return (i * 2);
}

static size_t
_right(size_t i)
{
    return (i * 2 + 1);
}

static void
_swap(size_t *p1, size_t *p2)
{
    size_t tmp;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


void
maxHeapify(T *a, size_t i, size_t len)
{
    size_t l = _left(i);
    size_t r = _right(i);
    size_t lagest;

    if (l <= len && a[i-1] < a[l-1])
        lagest = l;
    else 
        lagest = i;
    if (r <= len && a[lagest-1] < a[r-1])
        lagest = r;
    
    if (lagest != i) {
        _swap(&a[i-1], &a[lagest-1]);
        maxHeapify(a, lagest, len);
    }
}

void 
buildMaxHeap(T *arr, size_t len)
{
    size_t i;
    
    for (i = len/2; i >= 1; i--)
        maxHeapify(arr, i, len);
}

void static
_sort(T *arr, size_t len)
{
    size_t i;

    for (i = len; i >= 2; i--) {
        _swap(&arr[i-1], &arr[0]);
        len--;
        maxHeapify(arr, 1, len);
    }
}

void *
heapsort(void *addr, size_t len)
{
    buildMaxHeap((T *)addr, len);
    _sort((T *)addr, len);
    return (addr);
}

void 
print_arr(T *arr, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
