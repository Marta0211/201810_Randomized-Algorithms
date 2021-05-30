#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <ctime>
#include <algorithm>
using namespace std;

typedef vector<int> VE;

VE A;

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
		
		sort(A.begin(),A.end());
		
		int median = A[ceil(n/2.0)-1];
		t1 = clock();
		time = (double(t1-t0)/CLOCKS_PER_SEC);
		total_time += time;
		
		cout << "The median of the array is " << median << endl;
		cout << "Execution Time: " << time << endl;
		
	}
	cout << "Average execution time: " << (total_time)/100 << endl;
}
