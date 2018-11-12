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
  double weight;
  double price;
  double ratio;
    //reversing < operator for nodes so that sort function can properly sort the weights in a non-increasing order
    bool operator<(node a)
    {
        if(this->ratio > a.ratio)
        {
          return true;
        }
        return false;
    }
};
int maxProfit = 0;
int maxCapacity = 0;
void recursiveAlgorithmHelper(vector<node> list, vector<node> currentList, int index)
{
  int currentWeight = 0;
  int currentProfit = 0;
  if(index == list.size() + 1)
  {
    return;
  }
  for(int i = 0; i < currentList.size(); i++)
  {
    //cout << currentList[i].weight << " " << currentList[i].price << endl;
    currentWeight += currentList[i].weight;
    currentProfit += currentList[i].price;
  }
  //cout << "\n";
  //cout << "currentWeight is " << currentWeight << " and currentProfit is " << currentProfit << endl;
  if(currentWeight <= maxCapacity && currentProfit > maxProfit)
  {
    maxProfit = currentProfit;
  }
  currentList.push_back(list[index]);
  recursiveAlgorithmHelper(list, currentList, index + 1);
  currentList.pop_back();
  recursiveAlgorithmHelper(list, currentList, index + 1);
}
void recursiveAlgorithm(int capacity, vector<node> list)
{
  clock_t begin = clock();
  maxCapacity = capacity;
  vector<node> currentList;
  recursiveAlgorithmHelper(list, currentList, 0);
  clock_t end = clock();
  cout << list.size() << " " << maxProfit << " " << double(end - begin) / CLOCKS_PER_SEC << endl;
}

//reads the information from the input file into a vector of nodes
int main(int argc, char** argv)
{
  ifstream input_file;
  input_file.open(argv[1]);
  output_file.open(argv[2]);

  int alg = atoi(argv[3]);

  int itemCount = 0;
  int capacity = 0;
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
      temp.ratio = temp.price / temp.weight;
      list.push_back(temp);
    }
    //depending on the value specified in the command line, calls the proper algorithm on the data
    if(alg == 4)
    {
      recursiveAlgorithm(capacity, list);
    }
    list.clear();
  }
}
