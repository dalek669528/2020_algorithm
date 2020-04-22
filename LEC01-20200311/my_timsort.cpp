// C++ program for tim sort
#include <iostream>
#include <fstream>

using namespace std;
const int SIZE = 100;

// A utility function ot print an array of size n
void printArray(long int arr[], long int n){
    for (long int i=0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}



void timSort(long int arr[], long int n){
	for (long int i=1; i<n; i++){
		long int key = arr[i];
		long int j = i;
		while(j>0 && arr[j-1]>key){
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = key;
	}


}

// void timsort(long int arr[], long int n){



// }

// void timsort(long int arr[], long int n){



// }


int main(){
    // long int arr[] = {12, 11, 13, 5, 6, 1, 3, 2, 14, 19};
    
    long int arr[SIZE] = {0};
    ifstream fin("100K.in");
    for (long int i=0; i<SIZE; i++) {
    	  fin >> arr[i];	
	      //cout << i << ":" << arr[i] << " "; 		
    }
    		
    int n = sizeof(arr)/sizeof(arr[0]);
                
    timSort(arr, n);
    printArray(arr, n);
                         
    return 0;
}
