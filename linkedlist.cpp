#include <iostream>
#include <cstdio>

using namespace std;

#define MAX 1000;

int num[MAX];
int N;

typedef struct st {
} stack;


int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> num[i];
  }

  return 0;
}
