#include "HeapSort.h"

long long cmpCNTheapify(int* a, int start, int heapsize){
	long long count = 0;
	
	if(++count && start*2 + 1 >= heapsize) return count;
	
	int largerChildIdx = ((++count && a[start*2 + 1] > a[start*2 + 2]) || (++count && start*2 + 2 >= heapsize))? start*2 + 1 : start*2 + 2;
    
	if(++count && a[start] < a[largerChildIdx]){
		std::swap(a[start], a[largerChildIdx]);
		return cmpCNTheapify(a, largerChildIdx, heapsize) + count;
	}
	return count;
}
void heapify(int* a, int start, int heapsize){
	if(start*2 + 1 >= heapsize) return;
	
	int largerChildIdx = ((a[start*2 + 1] > a[start*2 + 2]) || start*2 + 2 >= heapsize)? start*2 + 1 : start*2 + 2;

	if(a[start] < a[largerChildIdx]){
		std::swap(a[start], a[largerChildIdx]);
		heapify(a, largerChildIdx, heapsize);
	}
} // These are now internal functions.
void Sort::Heap::Apply(int* a, int n){
	for(int i = (n-1)/2; i >= 0; i--)
		heapify(a, i, n);
	
	int HSize = n - 1;
	for(; HSize > 0; HSize--){
		std::swap(a[0], a[HSize]);
		heapify(a, 0, HSize);
	}
}
long long Sort::Heap::CountComparisons(int* a, int n){
    long long count = 0;
	for(int i = (n-1)/2; ++count && i >= 0; i--)
		count += cmpCNTheapify(a, i, n);
	
	int HSize = n - 1;
	for(; ++count && HSize > 0; HSize--){
		std::swap(a[0], a[HSize]);
		count += cmpCNTheapify(a, 0, HSize);
	}
	return count;
}
/*
Source: 
	ms Nhung's slides
	GeeksForGeeks: https://www.geeksforgeeks.org/heap-sort/
	educative.io: https://www.educative.io/answers/how-to-build-a-max-heap-using-an-array
*/