#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void count_sort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }


    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }


    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }


    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(int arr[], int n, int max_digits) {
    int exp = 1; 
    for (int i = 0; i < max_digits; i++) {
        count_sort(arr, n, exp);
        exp *= 10;
    }
}

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the value: ");
        scanf("%d", &arr[i]);
    }

    int max=arr[0];
    for (int i = 0; i < n; i++)
    {
    if(arr[i]>max){
        max=arr[i];
    }   
    }
    int p=0;
    while (max!=0)
    {
        max=max/10;
        p++;
    }
    
    

    radix_sort(arr, n, p);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
