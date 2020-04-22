// C++ program for insertion sort
#include <iostream>
#include <fstream>

using namespace std;
const int SIZE = 100;

void printArray(long int arr[], long int n);
/* Function to sort an array using insertion sort*/
void insertionSort(long int arr[], long int n)
{
    for(int i=1;i<n;i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0&&arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// A utility function ot print an array of size n
void printArray(long int arr[], long int n)
{
    for (long int i=0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
   
/* Driver program to test insertion sort */
int main()
{
    //long int arr[] = {12, 11, 13, 5, 6, 1, 3, 2, 14, 19};
    
    long int arr[SIZE] = {0};
    ifstream fin("100K.in");
    for (long int i=0; i<SIZE; i++) {
    	  fin >> arr[i];	
	      //cout << i << ":" << arr[i] << " "; 		
    }
    		
    int n = sizeof(arr)/sizeof(arr[0]);
                
    insertionSort(arr, n);
    printArray(arr, n);
                         
    return 0;
}
