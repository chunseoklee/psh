#include <iostream>
#include <cstdio>
#include <vector>


using namespace std;
#define MAX 5001

int N;
int i,j;
vector<int> e[MAX];
vector<int> te[MAX];

int s,t;
bool visited[MAX] = {false,};

int subafter1c[MAX] = {0,};

void make_tree(int index) {
  printf("make tree visit %d\n",index);
  visited[index] = true;

  for (i = 0; i < e[index].size(); i++) {
    if (visited[e[index][i]] == false) {
      te[index].push_back(e[index][i]);
      make_tree(e[index][i]);
    }
  }
}



int main(int argc, char *argv[])
{

  cin >> N;


  for (i = 0; i < N; i++) {

    cin >> s >> t;
    //cout << "read" << i << ":" << s << t << endl;
    e[s].push_back(t);
    e[t].push_back(s);
  }

  make_tree(1);

  return 0;
}
