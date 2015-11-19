#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define MAX 200001
#define H_MAX 900
int i,j;
int R,G;
int c[2][MAX];


int main(int argc, char *argv[])
{
  cin >> R >> G;
  int sum = R+G;
  int max_h;
  for (i = 1; i < 900; i++) {
    int node_needed = i*(i+1)/2;
    int node_needed_next = (i+1)*(i+2)/2;
    if (node_needed <= sum && node_needed_next > sum){
      max_h = i; break;
    }
  }


  for (i = 0; i <= R; i++) {
    c[0][i] = 1;
  }


  for (i = 1; i <= max_h; i++) {
    for (j = 1; j <= R; j++) {

        if (j >= i) {
          c[1][j] = c[0][j-i] + c[0][j];
        }

    }
    for (j = 1; j <= R; j++) {
      c[0][j] = c[1][j];
    }
  }

  cout << c[0][R];



  return 0;
}

// c[i][j] = c[i-1][j-i] + c[i-1][j]
