#include <iostream>

#define MAX 1501
using namespace std;

struct Edge
{
  int p1;
  int p2;
};

struct Point
{
  int x,y;
};

int N; // n of vertex in tree
struct Edge edges[MAX];
struct Point p[MAX];
void print_edges()
{
  for (int i=1; i <= N-1; i++) {
    cout << edges[i].p1 <<","<< edges[i].p2 << endl;
  }



}

void make_tree() {

  for (int i=1; i <= N; i++) {

  }
}

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i=1; i <= N-1; i++) {
    cin >> edges[i].p1 >> edges[i].p2;
  }

  print_edges();

  for (int i=1; i <= N; i++) {
    cin >> p[i].x >>  p[i].y;
  }

  make_tree();


  return 0;
}
