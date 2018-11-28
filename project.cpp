#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

ofstream output_file;
ofstream fib_output_file;

//structure used to store price, weight, and ratio for each value in the problem
struct node
{
  int weight;
  int price;
  bool operator<(node a)
  {
      if(this->weight < a.weight)
      {
        return true;
      }
      return false;
  }
};
int maxProfit = 0;
int maxCapacity = 0;
vector<node> completeList;

int itemCount = 0;
int capacity = 0;

int recursiveCount = 0;
void recursiveAlgorithmHelper(int currentWeight, int currentProfit, int index)
{
  if(index == completeList.size() + 1)
  {
    return;
  }
  recursiveCount++;
  if(currentWeight <= maxCapacity && currentProfit > maxProfit)
  {
    maxProfit = currentProfit;
  }
  recursiveAlgorithmHelper(currentWeight + completeList[index].weight, currentProfit + completeList[index].price, index + 1);
  recursiveAlgorithmHelper(currentWeight, currentProfit, index + 1);
}
void recursiveAlgorithm(int capacity, vector<node> list)
{
  clock_t begin = clock();
  maxCapacity = capacity;
  completeList = list;
  recursiveAlgorithmHelper(0, 0, 0);
  clock_t end = clock();
  output_file << "Divide & Conquer: " << list.size() << " " << recursiveCount << " " << maxProfit << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}
vector<vector<int> > arr;
void dynamicProgrammingAlgorithm(int capacity, vector<node> list)
{
  clock_t begin = clock();
  int c = capacity + 1;
  int item = list.size() + 1;
  arr.resize(item, vector<int>(c));
  /*for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      arr[i][j] = 0;
    }
  }
  */
  //sort(list.begin(), list.end());

  long count = 0;
  for(int i = 1; i < item; i++)
  {
    int wi = list[i-1].weight;
    int pi = list[i-1].price;
    for(int j = 1; j < c; j++)
    {
      count++;
      if(i == 0 || j == 0)
      {
        arr[i][j] = 0;
      }
      else if(wi <= j && arr[i-1][j-wi] + pi > arr[i-1][j])
      {
        arr[i][j] = arr[i-1][j-wi] + pi;
      }
      else
      {
        arr[i][j] = arr[i-1][j];
      }
    }
  }
  /*
  for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      cout << arr[i][j] << " ";
    }
    cout << "\n";
  }
  */
  clock_t end = clock();
  output_file << "Dynamic Programming: " << list.size() << " " << count << " " << arr[item - 1][c - 1] << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
  //cout << arr[1][capacity] << endl;
}
vector<node> memo_list;
long memocount = 0;
long repeatCount = 0;
int memoizedHelper(int i, int w)
{
  if(i > 0)
  {
    //cout << i << " " << w << endl;
    if(arr[i][w] != -1)
    {
      //cout << i << " " << w << endl;
      //repeatCount++;
      return arr[i][w];
    }
    memocount++;
    if(w < memo_list[i-1].weight)
    {
      arr[i][w] = memoizedHelper(i-1, w);
    }
    else
    {
      arr[i][w] = max(memoizedHelper(i-1, w), memo_list[i-1].price + memoizedHelper(i-1, w-memo_list[i-1].weight));
    }
  }
}
void memoizedAlgorithm(int capacity, vector<node> list)
{
  clock_t begin = clock();
  int c = capacity + 1;
  int item = list.size() + 1;
  arr.resize(item, vector<int>(c));
  for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      arr[i][j] = -1;
    }
  }
  memo_list = list;

  //sort(list.begin(), list.end());

  memoizedHelper(list.size(), capacity);
  //cout << memocount << endl;
  //cout << repeatCount << endl;
  clock_t end = clock();
  int i = item - 1;
  int w = c - 1;
  /*
  for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      cout << arr[i][j] << " ";
    }
    cout << "\n";
  }
*/
  output_file << "Memoization: " << list.size() << " " << memocount << " " << arr[item-1][c-1] << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
  //cout << arr[1][capacity] << endl;
}
void generateRandomFile(long items, long capacity)
{
  output_file << items << " " << capacity << endl;
  int w, p;
  for(int i = 0; i < items; i++)
  {
    w = rand() % 10 + 1;
    p = rand() % 100 + 1;
    output_file << w << " " << p << endl;
  }
}
//Aidan Memoization Code
long lookUpFib(int n, long A[]) {
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
void Fibonacci(int n) {
    clock_t begin = clock();
    long A[n + 1];
    for(int i = 0; i <= n; i++) {
        A[i] = -1;
    }
    long a = lookUpFib(n, A);
    clock_t end = clock();
    fib_output_file << "Memoization: " << n << " " << a << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}

//Jasper Dynamic Code
void fib(int n){
  clock_t begin = clock();
	long f[n+2];
	f[0] = 0;
	f[1] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = f[i-1] + f[i-2];
	}
  clock_t end = clock();
  fib_output_file << "Dynamic Programming: " << n << " " << f[n] << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}

int fibHelper(int n)
{
  if(n <= 1)
  {
    return n;
  }
  return fibHelper(n-2) + fibHelper(n-1);
}
void recursiveFib(int n)
{
  clock_t begin = clock();
  int a = fibHelper(n);
  clock_t end = clock();
  fib_output_file << "Divide & Conquer: " << n << " " << a << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}

//reads the information from the input file into a vector of nodes
int main(int argc, char** argv)
{
  ifstream input_file;
  ifstream fib_input_file;

  input_file.open(argv[1]);
  output_file.open(argv[2]);
  fib_input_file.open(argv[3]);
  fib_output_file.open(argv[4]);
  vector<node> list;

  //generateRandomFile(10000, 1000);

  while(input_file)
  {
    input_file >> itemCount;
    input_file >> capacity;
    if(input_file.eof())
      break;
    for(int i = 0; i < itemCount; i++)
    {
      node temp;
      input_file >> temp.weight;
      input_file >> temp.price;
      //temp.ratio = temp.price / temp.weight;
      list.push_back(temp);
    }
    //depending on the value specified in the command line, calls the proper algorithm on the data
    recursiveAlgorithm(capacity, list);
    dynamicProgrammingAlgorithm(capacity, list);
    memoizedAlgorithm(capacity, list);
    list.clear();
  }
  int a = 0;
  while(fib_input_file)
  {
    fib_input_file >> a;
    if(fib_input_file.eof())
      break;
    recursiveFib(a);
    fib(a);
    Fibonacci(a);
  }
}
