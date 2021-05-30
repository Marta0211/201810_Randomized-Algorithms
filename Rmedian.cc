#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <algorithm>
#include <ctime>
using namespace std;

typedef vector<int> VE;

VE A;
int error_vectors; 

void swap(VE &B, int i, int j) {
//Input: array B, indices i,j
//Output: swaps elements B[i] and B[j]

    int p = B[i];
    B[i] = B[j];
    B[j] = p;
}

int Ran_Partition(VE &B, int left, int right) {
// Input: B[left..right] = segment to be sorted
// Output: Index of the partition such that
//   B[index] = pivot
//   B[left..index-1] <= pivot
//   B[index+1..right] > pivot

    int ind = rand()%(right-left+1) + left;   // the index of pivot
    int x = B[ind];
    swap(ind,left); 
    int i= left; int j = right;
    while (i<j) {
        while (i <= right and B[i] <= x) ++i;
        while (j >= left and B[j] > x) --j;
        if (i < j) swap(i,j);
    }

    swap(left, j);
    return j;
}

VE DefineR(int t, VE A, int n) {
//Input: t size of R, array A, int n
//Output: array R containing a random and uniform sample of t elements of A
//        chosen with replacement
	
	VE R = VE(t);
	srand (time(NULL));
	for (int i=0; i<t; ++i) {
		//choose random element of A and place it in R[i]
		int index = rand()%n;
		R[i] = A[index];
	}
	return R;
}

int Rmedian(VE A, int n) {
//Input: array A, int n
//Output: Either -1 (fail) or median
	
	double p = pow((double)n, 3.0/4);
	int t = ceil(p);
	VE R = DefineR(t, A, n);
	sort(R.begin(), R.end()); 
	int index_d = floor(1.0/2*p - sqrt(n)); 
	if(index_d < 1) {
		cout << "error"<< endl;
		++error_vectors;
	}
	int index_u = ceil(1.0/2*p + sqrt(n));
	int d = R[index_d-1]; 
	int u = R[index_u-1];
	
	//Compute C, l_d, l_u
	VE C;
	int l_d = 0;
	int l_u = 0;
	for (int j=0; j<n; ++j) {
		if (A[j]>=d and A[j]<=u) {
			C.push_back(A[j]);
		}
		else if (A[j]<d) ++l_d;
		else ++l_u;
	}
	if (l_d > n/2.0 or l_u > n/2.0) {
		cout << "Fails due to l_d or l_u value" << endl;
		return -1;
	}
	cout << (int)C.size() << ' ' << 4*p<< endl;
	if ((int)C.size() > 4*p) {
		cout << "Fails due to C size" << endl;
		return -1;
	}
	else {
		sort(C.begin(), C.end());
		return C[floor(n/2)-l_d];
	}
}

int main() {
//Input: n and a 100xn matrix
//Output: Either median of the row or fail and execution time.
//Also outputs the average execution time, and total nber of fails.
	
	int n;
    cin >> n;
    A = VE(n, 0);
    
    unsigned t0, t1;
	double time, total_time;
	total_time = 0;
	int fail_vectors = 0;
	error_vectors = 0;
    
    for (int j=0; j<100; ++j) {
		for (int i=0; i<n; ++i)  cin >> A[i];
		
		t0=clock();
	
		int median = Rmedian(A,n);
		t1 = clock();
		time = (double(t1-t0)/CLOCKS_PER_SEC);
		total_time += time;
		
		
        if (median == -1) {
			cout << "FAIL" << endl;
			++fail_vectors;
		}
		else  cout << "The median of the array is " << median << endl;
		cout << "Execution Time: " << time << endl;
		
    
	}
	cout << endl;
	cout << "Fail vectors: " << fail_vectors << endl;
	if(error_vectors > 0) cout << "Error " << error_vectors << endl;
    cout << "Average execution time: " << (total_time)/100 << endl;
}
