#include "RadixSort.h"
#include <climits>

int getdigit(int n, int place){
    int digit = 0;
	for(int i = 0; i < place; i++){
		digit = n % 10; n /= 10;
	}
	return digit;
}

void internalCountingSRT(int* a, int n, int place){
    int max = INT_MIN;
	for(int i = 0; i < n; i++)
		if(getdigit(a[i], place) > max) max = getdigit(a[i], place);
	
	int* freq = new int[max + 1] {};
	
	
	for(int i = 0; i < n; i++)
		freq[getdigit(a[i], place)]++;	// update the freq arr
	for(int i = 1; i < max + 1; i++)
		freq[i] = freq[i] + freq[i-1];
	int* sorted = new int[n];
	
	for(int i = n-1; i >= 0; i--){
		sorted[freq[getdigit(a[i], place)] - 1] = a[i];
		freq[getdigit(a[i], place)]--;
	}

	for(int i = 0; i < n; i++)
		a[i] = sorted[i];
	delete []freq;
	delete []sorted;
}


long long cntCMPgetdigit(int n, int place, long long &count){
    int digit = 0;
	for(int i = 0; ++count && i < place; i++){
		digit = n % 10; n /= 10;
	}
	return digit;
}

long long cntCMPinternalCountingSRT(int* a, int n, int place){
    long long count = 0;
    int max = INT_MIN;
	for(int i = 0; ++count && i < n; i++)
		if(++count && cntCMPgetdigit(a[i], place, count) > max) max = cntCMPgetdigit(a[i], place, count);
	
	int* freq = new int[max + 1] {};
	
	
	for(int i = 0; ++count && i < n; i++)
		freq[cntCMPgetdigit(a[i], place, count)]++;	// update the freq arr
	for(int i = 1; ++count && i < max + 1; i++)
		freq[i] = freq[i] + freq[i-1];
	int* sorted = new int[n];
	
	for(int i = n-1; ++count && i >= 0; i--){
		sorted[freq[cntCMPgetdigit(a[i], place, count)] - 1] = a[i];
		freq[cntCMPgetdigit(a[i], place, count)]--;
	}

	for(int i = 0; ++count && i < n; i++)
		a[i] = sorted[i];
	delete []freq;
	delete []sorted;
    return count;
}


void Sort::Radix::Apply(int* a, int n){
    int max = INT_MIN;
	for(int i = 0; i < n; i++)
		if(a[i] > max) max = a[i];
	int i = 1;
	while(max > 0){
		internalCountingSRT(a, n, i);
		i++;
		max/=10;
	}
}

long long Sort::Radix::CountComparisons(int* a, int n){
    long long count = 0;
    
    int max = INT_MIN;
	for(int i = 0; ++count && i < n; i++)
		if(++count && a[i] > max) max = a[i];
	int i = 1;
	while(++count && max > 0){
		count += cntCMPinternalCountingSRT(a, n, i);
		i++;
		max/=10;
	}
    return count;
}