#include <cstdio>
#include <cstdlib> 
#include <iostream>
#include <climits>
using namespace std;

int SIZE;
void swap(int* a, int i, int j) {
    int tmp = a[j];
    a[j] = a[i];
    a[i] = tmp;
}
void printarray(int * a, int l, int r) { 
  for (int i=l; i<=r; i++) {
  	cerr << a[i] << " ";
  }
}

int partition(int* a, int l, int r) {
  // cout<<"--\n";
  // printarray(a, l, r);
  // cout<<"\n--\n";
  swap(a,(l+r)/2,r); //pick the middle as the pivot
  int p = l;
  for (int i=l; i<r; i++) {
      if (a[i]<=a[r]) {
          swap(a,i,p);
          p++;
    }
  } 
  swap(a,p,r);
return p;
}

//write your own code here!!!
int OrderStat(int arr[], int l, int r, int k) {

  if(l==r) return arr[l];
  int p = partition(arr, l, r);
  // i = p - l + 1;
  if(k==p) return arr[p];
  else if(k<p) OrderStat(arr, l, p-1, k);
  else OrderStat(arr, p+1, r, k);



}

// Driver program to test above methods
int main(int argc, char** argv ) {
  // your code here
  SIZE = atoi(argv[1]);
  // your code here
  int i;
  int* iary = new int[SIZE]; 
  srand(100); 	  
  for (i=0; i<SIZE; i++) {
  	iary[i] = rand()/1000000;
  }
  printarray(iary, 0, SIZE-1);
  cout << endl;
  
  int k = atoi(argv[2]);
  cout << k << "-th order statistics = " 
	   << OrderStat(iary, 0, SIZE-1, k) << endl;  
  return 0;	
}
