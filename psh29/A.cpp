#include <iostream>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100001

int T,K;


// c(p,0) is # of comb of length p
// with p-th char is B
// c(p,1) is with p-th W
int c[MAX][2] = { {0,0},};


int main(int argc, char *argv[])
{
  cin >> T >> K;

  c[0][0] = 0;
  c[0][1] = 0;
  for (int i = 1; i <= N; i++) {
    if (i >= k) { // ending with W
      c[i][1] = c[i-k][0] + c[i-k][1];
    }
    else {
      c[i][1] = 0;
    }

    c[i][0] =
  }


  // query
  int a,b;
  for(int i=1;i<=T;i++){
    cin >> a >> b;
  }


  return 0;
}
