#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <ctime>
using namespace std;

typedef vector<int> VE;

VE A;


void swap(int i, int j) {
//Input: indices i,j
//Output: swaps elements A[i] and A[j]

    int p = A[i];
    A[i] = A[j];
    A[j] = p;
}

int Ran_Partition(int left, int right) {
// Input: indices left, right st. A[left..right] = segment to be sorted
// Output: Index of the partition such that
//   A[index] = pivot
//   A[left..index-1] <= pivot
//   A[index+1..right] > pivot

    int ind = rand()%(right-left+1) + left;   // the index of pivot
    int x = A[ind];
    swap(ind,left); 
    int i= left; int j = right;
    while (i<j) {
        while (i <= right and A[i] <= x) ++i;
        while (j >= left and A[j] > x) --j;
        if (i < j) swap(i,j);
    }

    swap(left, j);
    return j;
}

int Qselect (int p, int q, int i) {
//Recursive function. If p==q returns element in that position
//Otherwise recurses in the subarray given by Ran_Partition where 
//i-th smaller element is.

	if (p==q) return A[p];
	
	else {
		int r = Ran_Partition(p,q);
		int k = r-p+1;
		if (i == k) return A[r];
		if (i < k) return Qselect(p,r-1,i);
		else return Qselect(r+1, q, i-k);
	}
	
}

int main() {
//Input: n and a 100xn matrix
//Output: Median of each row and execution time. Also average execution time.

    int n;
    cin >> n;
    A = VE(n,0);
    
    unsigned t0, t1;
	double time, total_time;
	total_time = 0;
	
    for (int j=0; j<100; ++j) {
		for (int i=0; i<n; ++i)  cin >> A[i];
		t0=clock();
	
		int median = Qselect(0,n-1, floor((n+1)/2));
		t1 = clock();
		time = (double(t1-t0)/CLOCKS_PER_SEC);
		total_time += time;
		
		cout << "The median of the array is " << median << endl;
		cout << "Execution Time: " << time << endl;
		
	}
	cout << "Average execution time: " << (total_time)/100 << endl;
}
