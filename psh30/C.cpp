#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define MAX 19

int N,M,K;
long long a[MAX];
vector<long long*> rules;
int i;

int main(int argc, char *argv[])
{
  cin >> N >> M >> K;
  for (i = 1; i <= N; i++) cin >> a[i];

  for (i = 1; i <= K; i++) {
    long long r[3];
    cin >> r[0] >> r[1] >> r[2];
    rules.push_back(r);
  }



  return 0;
}
// c[i][j] means max v when a[i] dish place at m-th
// c[i][j] =
// c[l][r][g] = c[l-1][r-l][g] + c[l-1][r][g-l]
// # of block below level i = i*(i+1)/2
// c[0][][] = 0;
// c[1]
