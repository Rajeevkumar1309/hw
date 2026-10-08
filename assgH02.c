#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

long count = 0;

int compareTwo(int first, int second){
    count = count + 1;
    if(first < second) return -1;
    if(first > second) return 1;
    return 0;
}

void swapTwo(int *first, int *second){
    int temp = *first;
    *first = *second;
    *second = temp;
}

void bubbleSort(int arr[], int size){
    int i, j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - 1 - i; j++){
            if(compareTwo(arr[j], arr[j+1]) > 0){
                swapTwo(&arr[j], &arr[j+1]);
            }
        }
    }
}

void mergeTwoHalves(int arr[], int start, int mid, int end){
    int i, j, k;
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    int leftArr[leftSize];
    int rightArr[rightSize];

    for(i = 0; i < leftSize; i++)
        leftArr[i] = arr[start + i];

    for(j = 0; j < rightSize; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;

    while(i < leftSize && j < rightSize){
        if(compareTwo(leftArr[i], rightArr[j]) <= 0){
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i < leftSize){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while(j < rightSize){
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int start, int end){
    if(start < end){
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        mergeTwoHalves(arr, start, mid, end);
    }
}

int partitionQuick1(int arr[], int low, int high){
    int randomPos = low + rand() % (high - low + 1);
    swapTwo(&arr[randomPos], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;
    int j;

    for(j = low; j < high; j++){
        if(compareTwo(arr[j], pivot) <= 0){
            i++;
            swapTwo(&arr[i], &arr[j]);
        }
    }

    swapTwo(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick1(int arr[], int low, int high){
    if(low < high){
        int pivotPos = partitionQuick1(arr, low, high);
        quick1(arr, low, pivotPos - 1);
        quick1(arr, pivotPos + 1, high);
    }
}

int getMedianOfThree(int arr[], int p1, int p2, int p3){
    if(compareTwo(arr[p1], arr[p2]) < 0){
        if(compareTwo(arr[p2], arr[p3]) < 0)
            return p2;
        else if(compareTwo(arr[p1], arr[p3]) < 0)
            return p3;
        else
            return p1;
    } else {
        if(compareTwo(arr[p1], arr[p3]) < 0)
            return p1;
        else if(compareTwo(arr[p2], arr[p3]) < 0)
            return p3;
        else
            return p2;
    }
}

int partitionQuick3(int arr[], int low, int high){
    int pivotIdx;
    if(high - low + 1 >= 3){
        int p1 = low + rand() % (high - low + 1);
        int p2 = low + rand() % (high - low + 1);
        int p3 = low + rand() % (high - low + 1);
        pivotIdx = getMedianOfThree(arr, p1, p2, p3);
    } else {
        pivotIdx = low;
    }
    swapTwo(&arr[pivotIdx], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;
    int j;

    for(j = low; j < high; j++){
        if(compareTwo(arr[j], pivot) <= 0){
            i++;
            swapTwo(&arr[i], &arr[j]);
        }
    }

    swapTwo(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick3(int arr[], int low, int high){
    if(low < high){
        int pivotPos = partitionQuick3(arr, low, high);
        quick3(arr, low, pivotPos - 1);
        quick3(arr, pivotPos + 1, high);
    }
}

int quickSelect(int arr[], int low, int high, int k){
    if(low == high) return low;
    int pivotPos = partitionQuick1(arr, low, high);
    if(k == pivotPos) return pivotPos;
    if(k < pivotPos) return quickSelect(arr, low, pivotPos - 1, k);
    return quickSelect(arr, pivotPos + 1, high, k);
}

int partitionQuickM(int arr[], int low, int high){
    int mid = (low + high) / 2;
    quickSelect(arr, low, high, mid);
    return mid;
}

void quickM(int arr[], int low, int high){
    if(low < high){
        int pivotPos = partitionQuickM(arr, low, high);
        quickM(arr, low, pivotPos - 1);
        quickM(arr, pivotPos + 1, high);
    }
}

int main(int argc, char *argv[]){

    int totalNumbers;
    if(argc > 1){
        totalNumbers = atoi(argv[1]);
    } else {
        printf("Enter how many numbers to generate: ");
        scanf("%d", &totalNumbers);
    }

    srand(time(NULL));
    int *original = malloc(totalNumbers * sizeof(int));
    int i;
    for(i = 0; i < totalNumbers; i++){
        original[i] = rand() % 1000000;
    }
    printf("Generated %d random numbers\n", totalNumbers);

    FILE *outputFile = fopen("output.txt", "w");

    int *arr = malloc(totalNumbers * sizeof(int));
    struct timeval startTime, endTime;
    double timeSec;

    memcpy(arr, original, totalNumbers * sizeof(int));
    count = 0;
    gettimeofday(&startTime, NULL);
    bubbleSort(arr, totalNumbers);
    gettimeofday(&endTime, NULL);
    timeSec = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Bubble Sort -> Comparisons: %ld  Time: %.6f seconds\n", count, timeSec);
    fprintf(outputFile, "%d %ld %.6f ", totalNumbers, count, timeSec);

    memcpy(arr, original, totalNumbers * sizeof(int));
    count = 0;
    gettimeofday(&startTime, NULL);
    mergeSort(arr, 0, totalNumbers - 1);
    gettimeofday(&endTime, NULL);
    timeSec = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Merge Sort  -> Comparisons: %ld  Time: %.6f seconds\n", count, timeSec);
    fprintf(outputFile, "%ld %.6f ", count, timeSec);

    memcpy(arr, original, totalNumbers * sizeof(int));
    count = 0;
    gettimeofday(&startTime, NULL);
    quick1(arr, 0, totalNumbers - 1);
    gettimeofday(&endTime, NULL);
    timeSec = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Quick1 Sort -> Comparisons: %ld  Time: %.6f seconds\n", count, timeSec);
    fprintf(outputFile, "%ld %.6f ", count, timeSec);

    memcpy(arr, original, totalNumbers * sizeof(int));
    count = 0;
    gettimeofday(&startTime, NULL);
    quick3(arr, 0, totalNumbers - 1);
    gettimeofday(&endTime, NULL);
    timeSec = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Quick3 Sort -> Comparisons: %ld  Time: %.6f seconds\n", count, timeSec);
    fprintf(outputFile, "%ld %.6f ", count, timeSec);

    memcpy(arr, original, totalNumbers * sizeof(int));
    count = 0;
    gettimeofday(&startTime, NULL);
    quickM(arr, 0, totalNumbers - 1);
    gettimeofday(&endTime, NULL);
    timeSec = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("QuickM Sort -> Comparisons: %ld  Time: %.6f seconds\n", count, timeSec);
    fprintf(outputFile, "%ld %.6f\n", count, timeSec);

    fclose(outputFile);
    printf("Results saved in output.txt\n");

    free(arr);
    free(original);

    return 0;
}