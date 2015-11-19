#include <iostream>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100001

int N,M;

vector<int> edge[MAX];
bool cat[MAX];
bool visited[MAX] = {false,};
int hecango = 0;
//int nofcat = 0;

void dfs(int index,int prevcat)
{
  bool isleaf = true;
  visited[index] = true;
  int nofcat = prevcat;

  if (cat[index]) nofcat++;
  else nofcat = 0;

  //  cout << "dfs:" << index << endl;
  //  cout << "nofcat:" << nofcat << endl;

  if (nofcat > M) return;



  for (int i = 0; i < edge[index].size(); i++) {
    int nextIndex = edge[index][i];
    if (visited[nextIndex] == false) {
      dfs(nextIndex, nofcat);
      isleaf = false;
    }
  }

  if (isleaf && nofcat <= M) {
    hecango++;
  }

}

int main(int argc, char *argv[])
{
  cin >> N >> M;

  for(int i=1;i<=N;i++){
    int catexist;
    cin >> catexist;

    if (catexist == 1) cat[i] = true;
    else cat[i] = false;
  }

  int s,t;
  for(int i=0;i<N-1;i++){
    cin >> s >> t;
    //cout << "push" << s <<"->"<< t<< endl;
    edge[s].push_back(t);
    edge[t].push_back(s);
  }

  dfs(1,0);

  cout << hecango << endl;





  return 0;
}
