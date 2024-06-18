#include <utility>
namespace Sort::Heap{
    void Apply(int* a, int n);
    long long CountComparisons(int* a, int n);
}

void heapify(int* a, int start, int heapsize);
long long cmpCNTheapify(int* a, int start, int heapsize);