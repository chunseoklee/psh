#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>

using namespace std;

#define MAX 100001

int N,M;
vector<int> outgoing[MAX];
vector<int> tree[MAX];
bool visited[MAX];
int parent[MAX];
int subtreesize[MAX];
int subtreelength[MAX];
int depth[MAX];

int indexleft[MAX];
int indexright[MAX];
vector<int> euler_seq;


void reset_visited() {
  for(int i=1; i<=MAX; i++) {
    visited[i] = false;
  }
}

/// make tree
int dfs(int r) {
  visited[r] = true;
  for(int i=0;i<outgoing[r].size();i++) {
    int ch = outgoing[r][i];
    if (!visited[ch]) {
      tree[r].push_back(ch);
      parent[ch] = r;
      dfs(ch);
    }
  }
}

/// sum up child node numbers
/// make tree
pair<int,int> sumup(int r,int d) {
  depth[r] = d;
  int sum = 0;
  int lengthsum = 0;
  for(int i=0;i<tree[r].size();i++) {
    int ch = tree[r][i];
    pair<int,int> result = sumup(ch,d+1);
    sum += result.first;
    //printf("%d's %d-th child's second=%d\n",r,i,result.second);
    lengthsum += result.second+(result.first);
  }
  //if (tree[r].size() == 0) { sum =1; } // leafnode
  sum++; // add 1 to sum;
  subtreesize[r] = sum;
  subtreelength[r] = lengthsum;
  //if (tree[r].size() == 0) return make_pair(sum,1);
  return make_pair(sum,lengthsum);
}

int uptreesize[MAX];
int uptreelength[MAX];

/// sum up parent node size, length
void uptree(int r,int plength, int psize) {

  uptreesize[r] = psize;
  uptreelength[r] = psize + plength;

  for(int i=0;i<tree[r].size();i++) {
    int ch = tree[r][i];
    int _psize = uptreesize[r] + subtreesize[r] - subtreesize[ch];
    int _plength = uptreelength[r] + subtreelength[r] - subtreelength[ch];
    uptree(ch,_plength, _psize);

  }
}



void print_tree(int r) {
  printf("node %d's parent: %d subsize: %d lengsum: %d depth: %d l:%d r:%d\n",r,parent[r],subtreesize[r],subtreelength[r],depth[r],indexleft[r],indexright[r]);
  for(int i=0;i<tree[r].size();i++) {
    int ch = tree[r][i];
    print_tree(ch);
  }
}

/// RMQ start
// A utility function to get minimum of two numbers
int minVal(int x, int y) { return (x < y)? x: y; }

// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) {  return s + (e -s)/2;  }

/*  A recursive function to get the minimum value in a given range
     of array indexes. The following are parameters for this function.

    st    --> Pointer to segment tree
    index --> Index of current node in the segment tree. Initially
              0 is passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment represented
                  by current node, i.e., st[index]
    qs & qe  --> Starting and ending indexes of query range */
int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
    // If segment of this node is a part of given range, then return
    //  the min of the segment
    if (qs <= ss && qe >= se)
        return st[index];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return INT_MAX;

    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                  RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}

// Return minimum of elements in range from index qs (quey start) to
// qe (query end).  It mainly uses RMQUtil()
int RMQ(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }

    return RMQUtil(st, 0, n-1, qs, qe, 0);
}

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }

    // If there are more than one elements, then recur for left and
    // right subtrees and store the minimum of two values in this node
    int mid = getMid(ss, se);
    st[si] =  minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                     constructSTUtil(arr, mid+1, se, st, si*2+2));
    return st[si];
}

/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for segment tree

    //Height of segment tree
    int x = (int)(ceil(log2(n)));

    // Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1;

    int *st = new int[max_size];

    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);

    // Return the constructed segment tree
    return st;
}

/// RMQ end

int level[MAX];
int leveltoindex[MAX];
int level_index = 1;
void make_level(int r) {
  level[r] = level_index++;
  leveltoindex[level[r]] = r;
  for(int i=0;i<tree[r].size();i++) {
    int ch = tree[r][i];
    make_level(ch);
  }
}

void euler_tour(int r) {
  euler_seq.push_back(level[r]);
  indexleft[r] = euler_seq.size()-1;
  for(int i=0;i<tree[r].size();i++) {
    int ch = tree[r][i];
    euler_tour(ch);
    euler_seq.push_back(level[r]);
  }
  //indexright[r] = euler_seq.size()-1;
}

void print_euler() {
  cout << "euler_seq: ";
  for(int i=0;i<euler_seq.size();i++) {
    printf("%d ",leveltoindex[euler_seq[i]]);
  }
  cout << endl;
}

int _rmq_array[MAX];
int* rmq_array;

int lca(int s,int t) {
  if (indexleft[s]>indexleft[t]) {int temp=s; s=t; t=temp;}
  int _lca = leveltoindex[RMQ(rmq_array, euler_seq.size(), indexleft[s] ,indexleft[t])];
   return _lca;
}


int main() {
  cin >> N >> M;
  // read graph
  int s,t;
  for(int i=1; i<=N-1; i++) {
    cin >> s >> t;
    outgoing[s].push_back(t);
    outgoing[t].push_back(s);
  }

  // make rooted tree
  reset_visited();
  dfs(1); // 1 as root;

  // sum up
  sumup(1,0);



  // construct rmq sequence
  make_level(1);
  euler_tour(1);
  //print_euler();
  //print_tree(1);
  // construct rmq
  for (int i=0;i<euler_seq.size();i++) {
    _rmq_array[i] = euler_seq[i];
  }
  rmq_array = constructST(_rmq_array, euler_seq.size());


  // solve queries

  for(int i=0; i<M; i++) {
    cin >> s >> t;
    int highnode = s; int lownode = t;
    int distance = 0;
    if ( depth[s] > depth[t] ) { highnode = t; lownode =s;}

    distance = depth[highnode] - depth[lca(highnode,lownode)] + depth[lownode] - depth[lca(highnode,lownode)];

    printf("distance  from %d to %d: %d\n",highnode,lownode,distance);


    int lowsize = subtreesize[lownode];
    int lowlength = subtreelength[lownode];

    // extract non-lower paths from children of highnode
    int highlength = subtreelength[highnode];
    int highsize = subtreesize[highnode];

    if (lca(highnode,lownode) == highnode) {
      //highsize = subtreesize[1] - subtreesize[highnode];
      //highlength = subtreelength[1] - subtreelength[highnode];
      for (int j=0;j<tree[highnode].size();j++) {
        int ch = tree[highnode][j];
        if (lca(ch,lownode) == ch) { // low is subtree of ch
          highsize -= subtreesize[ch];
          highlength -= (subtreelength[ch] + subtreesize[ch]);
        }
      }
    }


    printf("hs %d hl %d ls %d ll %d\n",highsize,highlength, lowsize, lowlength);

    double Answer = (highsize*lowlength + lowsize*highlength +
                    (highsize*lowsize)*distance + (highsize*lowsize))/ (double)(highsize*lowsize);
    printf("%f\n",Answer);

    //printf("rmq query from %d to %d: %d\n", indexleft[s],indexleft[t], leveltoindex[RMQ(rmq_array, euler_seq.size(), indexleft[s] ,indexleft[t])] );
  }

  return 0;
}
