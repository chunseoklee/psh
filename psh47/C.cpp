#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

#define MAX 1000000
#define LL int

LL N,M;

struct node {
  LL value; // original input value
  LL index; // original index
  vector< LL > outgoing;
  vector< LL > incoming;
  LL level;
};


node a[MAX];

void print_a() {
  for (LL i=0;i<=N-1;i++) {
    for (LL j=0;j<=M-1;j++) {
      printf("r:%lld c:%lld index:%lld v: %lld \n",i,j,a[i*M+j].index,a[i*M+j].value);
      for(int k=0;k<a[i*M+j].outgoing.size();k++) {
        printf("out edge from %lld to %lld\n",a[i*M+j].index,a[i*M+j].outgoing[k]);
      }
      for(int k=0;k<a[i*M+j].incoming.size();k++) {
        printf("in edge from %lld to %lld\n",a[i*M+j].incoming[k],a[i*M+j].index);
      }
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
//set < LL > unvisited;
vector< node > merged_g;
bool merged[MAX];
LL dfs_index;

void do_merging() {
  for(LL i=0;i<M*N;i++) {

  }
  for(LL i=0;i<M*N;i++) {
    if (merged[i] == false) {

    }
  }
}

bool visited[MAX];
LL  unvisited;

void dfs(LL index) {

  //printf("dfs at index %lld\n", index);
  //set< LL >::iterator it;
  //it = unvisited.find(index);
  //unvisited.erase(it);
  if(visited[index] == false) {
    visited[index] = true;
    unvisited--;
  }
  else {
    return;
  }

  for(LL i=0;i<a[index].outgoing.size();i++) {
    if(visited[a[index].outgoing[i]] == false)
       dfs(a[index].outgoing[i]);
  }
  dfs_seq.push_back(index);
}


int main() {
  // 1. read input
  cin >> N >> M;
  unvisited = M*N;

  for (LL i=0;i<=N-1;i++) {
    for (LL j=0;j<=M-1;j++) {
      a[i*(M)+j].index = i*M+j;
      scanf("%d ", &a[i*M+j].value);
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
      a[temp_row[j+1].index].incoming.push_back(temp_row[j].index);
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
    for (LL i=0;i<N-1;i++) {
      a[temp_col[i].index].outgoing.push_back(temp_col[i+1].index);
      a[temp_col[i+1].index].incoming.push_back(temp_col[i].index);
    }
  }
  //print_g();

  //2.5 merging graph
  //do_merging();


  // 3. build dfs seq
  // 3-1. unvisted set
  /*for(int i=0;i<M*N;i++) {
    unvisited.insert(i);
    }*/
  //3-2 dfs

  while(unvisited > 0) {
  //set< LL >::iterator it;
  //it = unvisited.begin();

    //find next unvisited
    for(LL i=dfs_index;i<M*N;i++) {
      if(visited[i] == false) {
        dfs_index = i;
        break;
      }
    }
    if (dfs_index == -1) {
      break;
    }

    dfs(dfs_index);
  }

  /*cout << "before reverse";
  for(int i=0;i<M*N;i++) {
    printf("%lld ",dfs_seq[i]);
    }*/

  reverse(dfs_seq.begin(), dfs_seq.end());

  /*cout << "After reverse";
  for(int i=0;i<M*N;i++) {
    printf("%lld ",dfs_seq[i]);
  }
  cout << endl;*/

  int cur_index;
  LL max_level;
  LL max_level_index;
  for(LL i=0;i<M*N;i++) {
    cur_index = dfs_seq[i];
    max_level = -100;
    for(LL ch=0;ch<a[cur_index].incoming.size();ch++){
      if(max_level < a[a[cur_index].incoming[ch]].level) {
        max_level = a[a[cur_index].incoming[ch]].level;
        max_level_index = a[cur_index].incoming[ch];
      }
    }
    if (a[cur_index].incoming.size() == 0) { a[cur_index].level = 1;}
    else {
      if (a[cur_index].value == a[max_level_index].value) {
        a[cur_index].level = max_level;
      }
      else {
        a[cur_index].level = max_level + 1;
      }
    }
  }

  int max = -1;
  for(LL i=0;i<N;i++) {
    for(int j=0;j<M;j++) {
      /*if (max < a[i*M+j].level) {
        max = a[i*M+j].level;
        }*/
      printf("%d ",a[i*M+j].level);
    }
    cout << endl;
  }

  //cout << max;
  //print_a();

  return 0;
}
