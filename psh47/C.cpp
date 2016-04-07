#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

#define MAX 1000000
#define LL long long

LL N,M;

struct node {
  LL value; // original input value
  LL index; // original index
  LL mergeindex; // index after merging
  vector< LL > outgoing;
  vector< LL > incoming;
};


node a[MAX];

void print_a() {
  for (LL i=0;i<=N-1;i++) {
    for (LL j=0;j<=M-1;j++) {
      LL out = -1;
      if (a[i*M+j].outgoing.size() != 0) { out = a[i*M+j].outgoing[0]; }
      printf("r:%lld c:%lld index:%lld v: %lld next:%lld ",i,j,a[i*M+j].index,a[i*M+j].value,out);
    }
    cout << endl;
  }
}

void print_g() {
  for (LL i=0;i<=N-1;i++) {

    for (LL j=0;j<=M-1;j++) {
    printf("(%lld, %lld):",i,j);
      for(int k=0;k<a[i*M+j].outgoing.size();k++) {
        printf("%lld ",a[i*M+j].outgoing[k]);
      }
    }
    cout << endl;
  }
}


bool cmpfunc (node i,node j) { return (i.value < j.value); }

node temp_row[MAX];
node temp_col[MAX];
vector< LL > dfs_seq;
set < LL > unvisited;
vector< node > merge_g;

void do_merging() {
  // 1. merge row one by one

  for (LL i=0;i<=N-1;i++) {
    LL curnode_index;
    // 1-1. pick smallest node
    for (LL j=0;j<=M-1;j++){
      if(a[i*M+j].incoming.size() == 0) {
        curnode_index = i*M+j;
        printf("r:%lld v:%lld\n ", i, a[curnode_index].value);
        break;
      }
    }
  }


}

void dfs(LL index) {

  //printf("dfs at index %lld\n", index);
  set< LL >::iterator it;
  it = unvisited.find(index);
  unvisited.erase(it);
  for(LL i=0;i<a[index].outgoing.size();i++) {
    if(unvisited.find(a[index].outgoing[i]) != unvisited.end())
       dfs(a[index].outgoing[i]);
  }
  dfs_seq.push_back(index);
}


int main() {
  // 1. read input
  cin >> N >> M;


  for (LL i=0;i<=N-1;i++) {
    for (LL j=0;j<=M-1;j++) {
      a[i*(M)+j].index = i*M+j;
      cin >> a[i*M+j].value;
    }
    //sort row
    //sort(a[i], a[i]+M, cmpfunc);
  }

  // 2. build graph
  // 2-1. build row graph
  for (LL i=0;i<=N-1;i++) {
    // copy temp_rwo
    for (LL j=0;j<M;j++) {
      temp_row[j] = a[i*M+j];
    }
    // sort
    sort(temp_row, temp_row+M, cmpfunc);
    // update graph
    for (LL j=0;j<=M-2;j++) {
      a[temp_row[j].index].outgoing.push_back(temp_row[j+1].index);
    }
  }

  // 2-2. build col graph
  for (LL j=0;j<=M-1;j++) {
    // copy temp_rwo
    for (LL i=0;i<N;i++) {
      temp_col[i] = a[i*M+j];
    }
    // sort
    sort(temp_col, temp_col+N, cmpfunc);
    // update graph
    for (LL j=0;j<N-1;j++) {
      a[temp_col[j].index].outgoing.push_back(temp_col[j+1].index);
      a[temp_col[j+1].index].incoming.push_back(temp_col[j].index);
    }
  }
  //print_g();

  //2.5 merging graph
  do_merging();


  // 3. build dfs seq
  // 3-1. unvisted set
  for(int i=0;i<M*N;i++) {
    unvisited.insert(i);
  }
  //3-2 dfs
  while(unvisited.size() > 0) {
    set< LL >::iterator it;
    it = unvisited.begin();
    dfs(*it);
  }

  reverse(dfs_seq.begin(), dfs_seq.end());

  for(int i=0;i<M*N;i++) {
    printf("%lld ",dfs_seq[i]);
  }
  cout << endl;


  return 0;
}
