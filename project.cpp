#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

ofstream output_file;

//structure used to store price, weight, and ratio for each value in the problem
struct node
{
  int weight;
  int price;
};
int maxProfit = 0;
int maxCapacity = 0;
vector<node> completeList;

int itemCount = 0;
int capacity = 0;


void recursiveAlgorithmHelper(int currentWeight, int currentProfit, int index)
{
  if(index == completeList.size() + 1 || currentWeight > maxCapacity)
  {
    return;
  }
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
  cout << list.size() << " " << maxProfit << " " << double(end - begin) / CLOCKS_PER_SEC << endl;
}
void dynamicProgrammingAlgorithm(int capacity, vector<node> list)
{
  clock_t begin = clock();
  int c = capacity + 1;
  int item = list.size() + 1;
  int arr[item][c];
  for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      arr[i][j] = 0;
    }
  }
  //sort(list.begin(), list.end());
  for(int i = 1; i < item; i++)
  {
    int wi = list[i-1].weight;
    int pi = list[i-1].price;
    for(int j = 1; j < c; j++)
    {
      if(wi <= j && arr[i-1][j-wi] + pi > arr[i-1][j])
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
  cout << "Dynamic Programming: " << list.size() << " " << arr[item - 1][c - 1] << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
  //cout << arr[1][capacity] << endl;
}
vector<node> memo_list;
vector<vector<int> > arr;
int memoizedHelper(int i, int w)
{
  if(i < 1)
  {
    return 0;
  }
  if(arr[i][w] < 0)
  {
    if(w < memo_list[i-1].weight)
    {
      arr[i][w] = memoizedHelper(i-1, w);
    }
    else
    {
      arr[i][w] = max(memoizedHelper(i-1, w), memo_list[i-1].price + memoizedHelper(i-1, w-memo_list[i-1].weight));
    }
  }
  return arr[i][w];
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

  //sort(list.begin(), list.end());
  memo_list = list;

  memoizedHelper(list.size(), capacity);
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
  cout << "Memoization: " << list.size() << " " << arr[item-1][c-1] << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
  //cout << arr[1][capacity] << endl;
}


//reads the information from the input file into a vector of nodes
int main(int argc, char** argv)
{
  ifstream input_file;
  input_file.open(argv[1]);
  vector<node> list;

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
    dynamicProgrammingAlgorithm(capacity, list);
    memoizedAlgorithm(capacity, list);
    list.clear();
  }
}
