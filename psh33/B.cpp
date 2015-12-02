#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
#define MAX 5001

int N;
vector<int> e[MAX];
vector<int> te[MAX];
vector<int> child[MAX];
set<int> comb;

int s,t;
bool visited[MAX] = {false,};
int parent[MAX];


void make_tree(int index) {
  visited[index] = true;

  for (int i = 0; i < e[index].size(); i++) {
    int next = e[index][i];
    if (visited[next] == false) {
      te[index].push_back(next);
      parent[next] = index;
      make_tree(next);
    }
  }
}


int count_child(int index) {
  int sum = 1;

  for (int i = 0; i < te[index].size(); i++) {
    int next = te[index][i];
    int temp = count_child(next);
    //printf("index: %d %d-th child num : %d\n", index, i ,temp);
    sum+=temp;
    child[index].push_back(temp);
  }

  return sum;
}

bool possible[MAX][MAX];

void compute_comb(vector<int> com)
{

  set<int> result;
  int sum = 0;

  int com_ar[MAX];

  sort(com.begin(),com.end());

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= com.size(); j++) {
      possible[i][j] = false;
    }
  }

  for (int j = 0; j < com.size(); j++) {
    com_ar[j+1] = com[j];
    //cout << "..."<< com[j] << ":";
    possible[com[j]][j+1] = true;
    sum += com[j];
  }
  //  cout << "sum " << sum << endl;
  for (int i = 1; i <= sum-1; i++) {
    for (int j = 1; j <= (com.size()); j++) {
      possible[i][j] = ( possible[i][j] || possible[i][j-1] );
      if (com_ar[j] <= i && !possible[i][j]){
        possible[i][j] = possible[i-com_ar[j]][j-1];
      }
      //printf("%d ",possible[i][j]);
    }
    //cout << endl;
  }

  for (int i = 1; i <= sum-1; i++) {
    if (possible[i][com.size()]) {
      //printf("possible:%d \n",i);
      comb.insert(i);
    }
  }
}


void solve()
{

  for (int i = 1; i <= N; i++) {
    vector<int> com;
    //printf("node %d child: %d parent: %d\n",i, child[i].size(),parent[i]);
    if (child[i].size() > 0 && parent[i] != 0) {
      int sum = 0;
      for (int j = 0; j < child[i].size(); j++) {
        sum += child[i][j];
        com.push_back(child[i][j]);
        //cout << "com pushed:" << child[i][j] << endl;
      }
      if (i != 1) {
        com.push_back(N-1-sum);
        //cout << "com pushed:" << (N-1-sum) << endl;
      }

      if (com.size() == 1){
      }
      else if (com.size() == 2) {
        comb.insert(com[0]);
        comb.insert(com[1]);
      } else {
        //printf("comb");
        compute_comb(com);
      }
    }
  }



}

int main(int argc, char *argv[])
{

  cin >> N;


  for (int i = 0; i < N-1; i++) {

    cin >> s >> t;
    e[s].push_back(t);
    e[t].push_back(s);

  }

  parent[1] = 1;
  make_tree(1);

  count_child(1);


  solve();

  cout << comb.size() << endl;
  for( set<int>::iterator IterPos = comb.begin();
       IterPos != comb.end(); ++IterPos ) {
    cout << *IterPos << " " << N-1-(*IterPos) << endl;
  }

  return 0;
}
