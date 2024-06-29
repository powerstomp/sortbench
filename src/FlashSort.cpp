#include "FlashSort.h"

void Sort::Flash::Apply(int* data, int n) {
//send help
    if (n <= 1) return; 

    int bucketCount = floor(n * 0.45);
    std::vector<int> elementCounts(bucketCount, 0);

    int minVal = data[0],  maxVal = data[0];
    for(int i = 1; i < n; i++)
    {
        if(data[i] < minVal)
            minVal = data[i];
        if(data[i] > maxVal)
            maxVal = data[i];
    }
    if(minVal == maxVal) return;

    for(int i = 0; i < n; i++)
    {
        int curBucket = static_cast<int>((data[i] - minVal) * bucketCount / (maxVal - minVal));
        if(data[i] == maxVal) curBucket = bucketCount-1;
        elementCounts[curBucket]++;
    }
    for(int i = 1; i < bucketCount; i++)
    {
        elementCounts[i] += elementCounts[i-1];
    }

    //put stuffs in correct bucket
    int count = 0, index = 0;
    while(count < n)
    {
        int curBucket = int((data[index] - minVal) * bucketCount / (maxVal - minVal));
        if(data[index] == maxVal) curBucket = bucketCount-1;
        while(index >= elementCounts[curBucket] && index < n)
        {
            index++;
            curBucket = static_cast<int>((data[index] - minVal) * bucketCount / (maxVal - minVal));
            if(data[index] == maxVal) curBucket = bucketCount-1;
        }
        //swap
        while(index < elementCounts[curBucket])
        {
            int temp = data[index];
            elementCounts[curBucket]--;
            data[index] = data[elementCounts[curBucket]];
            data[elementCounts[curBucket]] = temp;
            index++;
            curBucket = static_cast<int>((data[index] - minVal) * bucketCount / (maxVal - minVal));
            if(data[index] == maxVal) curBucket = bucketCount-1;
            count++;
        }
    }

    for(int i = 1; i < n; i++){
		int key = data[i], j = i - 1;
		while(j >= 0 && data[j] > key){
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}

    return;
}

long long Sort::Flash::CountComparisons(int* data, int n) {
    long long res = 0;

    if (++res && n <= 1) return res; 

    int bucketCount = floor(n * 0.45);
    if(bucketCount < 1) bucketCount = 1;
    std::vector<int> elementCounts(bucketCount, 0);

    int minVal = data[0],  maxVal = data[0];
    for(int i = 1; ++res && i < n; i++)
    {
        if(++res && data[i] < minVal)
            minVal = data[i];
        if(++res && data[i] > maxVal)
            maxVal = data[i];
    }
    if(++res && minVal == maxVal) return res;

    for(int i = 0; ++res && i < n; i++)
    {
        int curBucket = static_cast<int>((data[i] - minVal) * bucketCount / (maxVal - minVal));
        elementCounts[curBucket]++;
    }
    for(int i = 1; ++res && i < bucketCount; i++)
    {
        elementCounts[i] += elementCounts[i-1];
    }

    //put stuffs in correct bucket
    int count = 0, index = 0;
    while(++res && count < n)
    {
        int curBucket = static_cast<int>((data[index] - minVal) * bucketCount / (maxVal - minVal));
        while(++res && index >= elementCounts[curBucket])
        {
            index++;
            curBucket = static_cast<int>((data[index] - minVal) * bucketCount / (maxVal - minVal));
        }
        //swap
        while(++res && index < elementCounts[curBucket])
        {
            int temp = data[index];
            elementCounts[curBucket]--;
            data[index] = data[elementCounts[curBucket]];
            data[elementCounts[curBucket]] = temp;
            index++;
            curBucket = static_cast<int>((data[index] - minVal) * bucketCount / (maxVal - minVal));
            count++;
        }
    }

    for(int i = 1; ++res && i < n; i++){
		int key = data[i], j = i - 1;
		while(++++res && j >= 0 && data[j] > key){
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}

    return res;
}
