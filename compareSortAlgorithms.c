#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int  extraMemoryAllocated;
void merge(int pData[], int left, int middle, int right) {

    int i, j, k;
    int number1 = middle - left + 1;
    int number2 = right - middle;
    int left_array[number1], right_array[number2];

    extraMemoryAllocated = extraMemoryAllocated + sizeof(left) + sizeof(right);

    for (i = 0; i < number1; i++)
        left_array[i] = pData[left + i];
    for (j = 0; j < number2; j++)
        right_array[j] = pData[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < number1 && j < number2) {
        if (left_array[i] <= right_array[j]) {
            pData[k] = left_array[i];
            i++;
        } else {
            pData[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < number1) {
        pData[k] = left_array[i];
        i++;
        k++;
    }

    while (j < number2) {
        pData[k] = right_array[j];
        j++;
        k++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {

    int i, j, item = pData[i];
    /* Move elements of arr[0..i-1], that are
greater than key, to one position ahead
of their current position */
    for (j = i - 1; j >= 0; j--) {
        if (pData[j] > item)
            pData[j + 1] = pData[j];
        else
            break;
    }
    pData[j + 1] = item;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {

    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pData[j] > pData[j + 1]) { //then swap
                temp         = pData[j];
                pData[j]     = pData[j + 1];
                pData[j + 1] = temp;
            }
            printArray(pData, n);
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {

    int i, j, min_idx, temp;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (pData[j] < pData[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        temp           = pData[i];
        pData[i]       = pData[min_idx];
        pData[min_idx] = temp;
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int   dataSz = 0;
    *ppData      = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int*)malloc(sizeof(int) * dataSz);
        if (*ppData) {
            for (int i = 0; i < dataSz; i++) {
                fscanf(inFile, "%d\n", &((*ppData)[i]));
            }
        }
    }
    fclose(inFile);
    return dataSz;
}
// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\t");

    for (i = sz; i < dataSz; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\n");
}

int main(void) {
    clock_t start, end;
    int     i;
    double  cpu_time_used;
    char*   fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

    for (i = 0; i < 3; ++i) {
        int *pDataSrc, *pDataCopy;
        int  dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int*)malloc(sizeof(int) * dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start                = clock();
        selectionSort(pDataCopy, dataSz);
        end           = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start                = clock();
        insertionSort(pDataCopy, dataSz);
        end           = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start                = clock();
        bubbleSort(pDataCopy, dataSz);
        end           = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start                = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end           = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }
    return 0;
}