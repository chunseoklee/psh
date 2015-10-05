#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>



using namespace std;

#define MAX 501



bool visited[MAX][MAX];


int r,c;
int r1,c1,r2,c2;
int mat[MAX][MAX];
bool onestep = false;



int countD(int ri,int ci) {
  int ret = 0;
  if(mat[ri-1][ci] == 1) {
    ret++;
  }
  if(mat[ri+1][ci] == 1) {
    ret++;
  }

  if(mat[ri][ci+1] == 1) {
    ret++;
  }

  if(mat[ri][ci-1] == 1) {
    ret++;
  }

  return ret;
}

bool dfs(int ri,int ci) {
  //cout << "visit: " << ri << "," << ci << endl;
  bool found = false;

  if ((ri != r2 || ci != c2)) {
    visited[ri][ci] = true;
  }



  if (onestep) {
    if (ri == r2 && ci == c2 ) {
      if (mat[r2][c2] == 0 || countD(ri,ci) >= 2) {
        return true;
      }
      else {
        return false;
      }

    }
    else {
      if (mat[ri][ci] == 0) {
        return false;
      }
    }
  }


  onestep = true;
  if ((ri != r1 && ci != c1) && mat[ri][ci] == 0) {
    return false;
  }

  if (!visited[ri-1][ci] && ri > 1) {
    if (dfs(ri-1,ci)) {
      return true;
    }
  }

  if (!visited[ri+1][ci] && ri < r) {
    if (dfs(ri+1,ci)) {
      return true;
    }
  }

  if (!visited[ri][ci-1] && ci > 1) {
    if (dfs(ri,ci-1)) {
      return true;
    }
  }

  if (!visited[ri][ci+1] && ci < c) {
    if (dfs(ri,ci+1)) {
      return true;
    }
  }

  return false;

}





int main(int argc, char *argv[])
{

  cin >> r >> c;


  for (int i = 1; i <= r; i++) {
    char buf[MAX];
    cin >> buf;
    for (int j = 0; j < c; j++) {
      if (buf[j] == '.') {
        mat[i][j+1] = 1;
      }
      else {
        mat[i][j+1] = 0;
      }
      //cout << mat[i][j+1];
    }
    //cout << endl;
  }

  cin >> r1 >> c1 >> r2 >> c2;

  //2. construct graph

  //construct();

  // end of input

  //3. dfs from (r1,c1)
  if(dfs(r1,c1)) {
    cout << "YES";
  }
  else {
    cout << "NO";
  }


  return 0;
}
