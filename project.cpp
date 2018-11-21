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
  cout << "Divide & Conquer: " << list.size() << " " << maxProfit << " " << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}
vector<vector<int> > arr;
void dynamicProgrammingAlgorithm(int capacity, vector<node> list)
{
  int c = capacity + 1;
  int item = list.size() + 1;
  arr.resize(item, vector<int>(c));
  for(int i = 0; i < item; i++)
  {
    for(int j = 0; j < c; j++)
    {
      arr[i][j] = 0;
    }
  }
  //sort(list.begin(), list.end());
  clock_t begin = clock();
  long count = 0;
  for(int i = 1; i < item; i++)
  {
    int wi = list[i-1].weight;
    int pi = list[i-1].price;
    for(int j = 1; j < c; j++)
    {
      count++;
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
  cout << count << endl;
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
long memocount = 0;
int memoizedHelper(int i, int w)
{
  if(i > 0)
  {
    memocount++;
    //cout << i << " " << w << endl;
    if(arr[i][w] != -1)
    {
      return arr[i][w];
    }
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

  clock_t begin = clock();
  memoizedHelper(list.size(), capacity);
  cout << memocount << endl;
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
    //recursiveAlgorithm(capacity, list);
    dynamicProgrammingAlgorithm(capacity, list);
    memoizedAlgorithm(capacity, list);
    list.clear();
  }
}