#include "InsertionSort.h"

void Sort::Insertion::Apply(int* a, int n){
	for(int i = 1; i < n; i++){// for some reason this was 4 spaces and not 1 tab
		int key = a[i], j = i - 1;
		while(j >= 0 && a[j] > key){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
long long Sort::Insertion::CountComparisons(int* a, int n){
	long long comp = 0;
	for(int i = 1; ++comp && i < n; i++){
		int key = a[i], j = i - 1;
		while((++comp && j >= 0) && (++comp && a[j] > key)){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
	return comp;
}
/*
Source: 
	ms Nhung's slides
*/