#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <chrono>
#include <iostream>

using namespace std;

int lookUpFib(int n, int A[]) {
    if(A[n] == -1) {
        if(n <= 1) {
            A[n] = n;
        }
        else {
            A[n] = lookUpFib(n - 1, A) + lookUpFib(n - 2, A);
        }
    }
    return A[n];
}

int Fibonacci(int n) {
    int A[n + 1]; 
    for(int i = 0; i <= n; i++) {
        A[i] = -1;
    }
    return lookUpFib(n, A);
}

int main() {
    int ret = Fibonacci(40);
    cout << ret << endl;
    return 0;
}
