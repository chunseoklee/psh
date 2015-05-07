#include <iostream>
#include <cstdio>

using namespace std;


int main(int argc, char *argv[])
{
  int N;
  int X;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> X;
    if(X%2==0){
      cout << X << endl;
    }
    else{
      cout << X-1 << endl;
    }
  }

  return 0;
}
