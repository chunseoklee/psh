#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <assert.h>
#include <cstdio>
using namespace std;

#define MAX 100000

int N;
int numbers[MAX];

void print_nums()
{
  for (int i = 0; i < N; i++) {
    cout << numbers[i] << ",";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> numbers[i];
  }
  print_nums();



  return 0;
}
