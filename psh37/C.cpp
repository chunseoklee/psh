#include <iostream>
#include <set>
#include <cstdio>


using namespace std;

int N;
int comb[6][3];
int a,b,c;
multiset<int> ms;
multiset<int>::iterator it;

int main(int argc, char *argv[])
{
  cin >> N;
  cin >> a >> b >> c;

  comb[1][0] = a+b+c;
  comb[2][0] = b+c; comb[2][1] = a;
  comb[3][0] = a+c; comb[3][1] = b;
  comb[4][0] = ((a+b)>=c?(a+b):c); comb[4][1] = ((a+b)<=c?(a+b):c);
  comb[5][0] = c; comb[5][1] = b; comb[5][2] = a;

  /*
  printf("a: %d b: %d c: %d\n",a,b,c);

  for (int i = 0; i < 5; ++i) {

    printf("%d-th %d %d %d\n ",i,comb[i][0],comb[i][1],comb[i][2]);
    }*/
  int c;
  for (int i = 1; i <= N; ++i) {
    cin >> c;
    ms.insert(c);
  }


  return 0;
}
