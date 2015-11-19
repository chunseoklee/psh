#include <iostream>
#include <cstdio>
#include <vector>


using namespace std;
#define MAX 100001

int N;
vector<int> e[MAX];
vector<int> te[MAX];
vector<int> b[MAX];
vector<int> tb[MAX];

int s,t,bad;
bool visited[MAX] = {false,};
int bad_child[MAX] = {0,};
int parent[MAX];
bool parent_bad[MAX] = {false,};

void make_tree(int index) {
  //  printf("make tree visit %d\n",index);
  visited[index] = true;

  for (int i = 0; i < e[index].size(); i++) {
    int next = e[index][i];
    int nextb = b[index][i];
    if (visited[next] == false) {
      te[index].push_back(next);
      tb[index].push_back(nextb);
      parent[next] = index;
      make_tree(next);
    }
  }
}

int count_badedge_below_node(int index) {

  if (te[index].size() == 0) { // leaf
    return 0;
  }

  int n_bad = 0;

  for (int i=0; i<te[index].size();i++) {

    int next = te[index][i];
    int nextb = tb[index][i];
    //cout << "next" << next << endl;
    if (nextb == 2 ){
      n_bad++;
      parent_bad[next] = true;
    }
    n_bad += count_badedge_below_node(next);
  }

  bad_child[index] = n_bad;
  return n_bad;
}


void solve()
{
  vector<int> result;
  for( int i = 1; i <= N; i++ ){
    if (parent_bad[i] && bad_child[i] == 0) {
      result.push_back(i);
    }
  }
  cout << result.size() << endl;
  for( int i = 0; i <result.size(); i++ ){
    cout << result[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{

  cin >> N;


  for (int i = 0; i < N-1; i++) {

    cin >> s >> t >> bad;

    e[s].push_back(t);
    b[s].push_back(bad);
    e[t].push_back(s);
    b[t].push_back(bad);
  }

  make_tree(1);

  count_badedge_below_node(1);

  solve();

  return 0;
}
