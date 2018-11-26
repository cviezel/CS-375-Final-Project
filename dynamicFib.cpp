#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int fib(int n){
	int f[n+2];
	f[0] = 0;
	f[1] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = f[i-1] + f[i-2];
	}
	return f[n];
}

int main(){
	int n = 9;
	cout << "Term: " << n << endl << "Fib Number: " << fib(n) << endl;
	return 0;
}
