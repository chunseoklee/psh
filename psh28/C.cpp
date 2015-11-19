#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX 30001

int N,P;
vector<int> edge[MAX];
bool visited[MAX] = {false,};
//int i,j,k;
queue<int> q;


void dfs(int index)
{
  visited[index] = true;

  for (int i = 0; i < edge[index].size(); i++) {
    int nextIndex = edge[index][i];
    if ( visited[nextIndex] == false) {
      dfs(nextIndex);
    }
  }

  q.push(index);

}


int main(int argc, char *argv[])
{
  cin >> N >> P;

  int s,t;
  for(int i=0;i<P;i++){
    cin >> s >> t;
    edge[s].push_back(t);
  }

  for (int i = 1; i <= N; i++) {
    if (visited[i] == false) {
      dfs(i);
    }
  }


  while (!q.empty()) {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl;

  return 0;
}
