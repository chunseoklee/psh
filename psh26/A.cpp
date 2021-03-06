#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

bool visited[301] = {false,};

int input[301];
int N;
int mat[301][301];
int result[301];
vector<int> dfsindex;
vector<int> dfsvalue;


void dfs(int index) {
  //cout << "dfs: " << index << "\n";
  visited[index] = true;
  dfsindex.push_back(index);
  dfsvalue.push_back(input[index]);

  for (int i=1; i<=N; i++) {
    if (!visited[i] && mat[index][i] == 1) {
      dfs(i);
    }
  }
}

int main(int argc, char *argv[])
{
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> input[i];
  }

  for (int i = 1; i <= N; i++) {
    char buf[302];
    cin >> buf;
    for (int j = 0; j < N; j++) {
      if (buf[j] == '1') {
        mat[i][j+1] = 1;
      }
      else {
        mat[i][j+1] = 0;
      }
      //cout << mat[i][j+1];
    }
    //cout << endl;
  }

  for (int i=1; i<=N; i++) {
    if (visited[i] == false) {
      //1. DFS and make a set
      dfs(i);
      //cout << "dfs: " << i << "=>";
      std::sort (dfsindex.begin(), dfsindex.end());
      std::sort (dfsvalue.begin(), dfsvalue.end());
      for(int j=0; j<dfsindex.size();j++) {
        //cout << dfslist[j] << " ";
        result[dfsindex[j]] = dfsvalue[j];
      }
      dfsindex.clear();
      dfsvalue.clear();
      //2. update result array using list of step 1
    }
  }

  for (int i=1; i<=N; i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}
