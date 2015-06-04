#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <assert.h>
#include <cstdio>
using namespace std;

#define MAX 100000

int N;
int nofarcs;

struct arc {
  arc(int v1_, int v2_) { v1 = v1_; v2= v2_;}
  int v1,v2;
};

vector<int> adv[MAX];
vector<arc> arcs;


void print_adv()
{
   for (int i = 1; i <= N; i++) {
     cout << "v: "<< i << endl;
     for (int j = 0; j < adv[i].size(); j++) {
       std::cout << adv[i][j] << " ";

     }
     std::cout << std::endl;

   }
}

bool arc_cmp(const arc& a, const arc& b){
  if(a.v1 < b.v1){
    return true;
  }
  else if (a.v1 == b.v1 && a.v2 < b.v2){
    return true;
  }

  return false;
}

void print_arcs()
{
  for (int i = 0; i < arcs.size(); i++) {
    std::cout << "(" << arcs[i].v1 << " " << arcs[i].v2 << ") ";
  }
  std::cout << std::endl;
}

class CircularL {
public:
  CircularL():length(0){ }
  void insert(int v_){
    vlist.push_back(v_);
    length++;
  }
  int length;
  vector<int> vlist;
};


int main(int argc, char *argv[])
{
  cin >> N;
  nofarcs = N*2;

  for (int i = 1; i <= nofarcs; i++) {
    int v1,v2;
    cin >> v1 >> v2;
    if(v1 > v2){
      int temp = v2;
      v2 = v1;
      v1 = temp;
    }
    adv[v1].push_back(v2);
    adv[v2].push_back(v1);
    arcs.push_back(arc(v1,v2));

  }
  sort(arcs.begin(), arcs.end(), arc_cmp);

  //print_adv();
  //print_arcs();

  //binary_search(arcs.begin(),  arcs.end(), arc(1,1), arc_cmp));

  if(N == 5){
    for (int i = 1; i <= N; i++) {
      if(adv[i].size() != 4){
        cout << -1;
        return 0;
      }
    }
    cout << "1 2 3 4 5";
  }
  else if (N==6){

  }
  else {

  }



  return 0;
}
