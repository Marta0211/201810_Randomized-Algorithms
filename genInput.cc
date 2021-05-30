#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <ctime>
using namespace std;

typedef vector<int> VE;

//Generates 100 entries.
//Please uncomment the type of entry you want and change n value.
//Default is constant entry equal to 1.

int main() {
	int n = 5e2;
	VE A = VE(n,1);
	cout << n << endl;
	srand (time(NULL));
	for (int j=0; j<100; ++j) {
		for (int i=0; i<n; ++i) {
			//A[i]= rand()%100;  //random input in range [0,99]
			//A[i]= rand()%3;   //random input in range [0,2]
			//A[i] = i;       //sorted in ascending order
			//A[i] = n-i;     //sorted in descending order
			cout << A[i] << ' ';
		}
		cout << endl;
	}
	
}
