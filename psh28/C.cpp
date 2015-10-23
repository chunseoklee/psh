#include <iostream>
#include <cstdio>

using namespace std;

#define MAX 30000

int N;
int ar[MAX];
int edge[MAX][MAX];
int degree[MAX] = {0,};
bool visited[MAX] = {false,};


void dfs(int index)
{

}

int main(int argc, char *argv[])
{
  cin >> N;

  int s,t;
  for(int i=0;i<N;i++){
    cin >> t >> s;
    edge[s][degree[s]] = t;
    degree[s] += 1;
  }

  for (int i = 0; i < N; i++) {

  }



  return 0;
}
