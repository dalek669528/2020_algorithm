// C program for insertion sort
#include <stdio.h>
#include <math.h>
 
int arr[] = {12, 11, 13, 5, 6, 1, 3, 2, 14, 19};

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    //write your own code here!!!

} 

// A utility function ot print an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
   
/* Driver program to test insertion sort */
int main()
{
    int n = sizeof(arr)/sizeof(arr[0]);
                
    insertionSort(arr, n);
    printArray(arr, n);
                         
    return 0;
}
