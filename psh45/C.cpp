#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <iomanip>
using namespace std;

#define MAX 100001

long long N,M;
vector<int> outgoing[MAX];
vector<int> tree[MAX];
bool visited[MAX];
long long parent[MAX];
long long subtreesize[MAX];
long long subtreelength[MAX];
long long depth[MAX];

long long indexleft[MAX];
long long indexright[MAX];
vector<int> euler_seq;


void reset_visited() {
  for(long long i=1; i<=MAX; i++) {
    visited[i] = false;
  }
}

/// make tree
long long dfs(long long r) {
  visited[r] = true;
  for(long long i=0;i<outgoing[r].size();i++) {
    long long ch = outgoing[r][i];
    if (!visited[ch]) {
      tree[r].push_back(ch);
      parent[ch] = r;
      dfs(ch);
    }
  }
}

/// sum up child node numbers
/// make tree
pair<long long,long long> sumup(long long r,long long d) {
  depth[r] = d;
  long long sum = 0;
  long long lengthsum = 0;
  for(long long i=0;i<tree[r].size();i++) {
    long long ch = tree[r][i];
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

long long uptreesize[MAX];
long long uptreelength[MAX];

/// sum up parent node size, length
void uptree(long long r,long long plength, long long psize) {

  uptreesize[r] = psize;
  uptreelength[r] = psize + plength;

  for(long long i=0;i<tree[r].size();i++) {
    long long ch = tree[r][i];
    long long _psize = uptreesize[r] + subtreesize[r] - subtreesize[ch];
    long long _plength = uptreelength[r] + subtreelength[r] - subtreelength[ch]- subtreesize[ch];
    uptree(ch,_plength, _psize);
  }
}



void print_tree(long long r) {
  printf("node %d's parent: %d subsize: %d lengsum: %d depth: %d l:%d r:%d us: %d ul: %d\n",r,parent[r],subtreesize[r],subtreelength[r],depth[r],indexleft[r],indexright[r],uptreesize[r],uptreelength[r]);
  for(long long i=0;i<tree[r].size();i++) {
    long long ch = tree[r][i];
    print_tree(ch);
  }
}

/// RMQ start
// A utility function to get minimum of two numbers
long long minVal(long long x, long long y) { return (x < y)? x: y; }

// A utility function to get the middle index from corner indexes.
long long getMid(long long s, long long e) {  return s + (e -s)/2;  }

/*  A recursive function to get the minimum value in a given range
     of array indexes. The following are parameters for this function.

    st    --> Pointer to segment tree
    index --> Index of current node in the segment tree. Initially
              0 is passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment represented
                  by current node, i.e., st[index]
    qs & qe  --> Starting and ending indexes of query range */
long long RMQUtil(long long *st, long long ss, long long se, long long qs, long long qe, long long index)
{
    // If segment of this node is a part of given range, then return
    //  the min of the segment
    if (qs <= ss && qe >= se)
        return st[index];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return INT_MAX;

    // If a part of this segment overlaps with the given range
    long long mid = getMid(ss, se);
    return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                  RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}

// Return minimum of elements in range from index qs (quey start) to
// qe (query end).  It mainly uses RMQUtil()
long long RMQ(long long *st, long long n, long long qs, long long qe)
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
long long constructSTUtil(long long arr[], long long ss, long long se, long long *st, long long si)
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
    long long mid = getMid(ss, se);
    st[si] =  minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                     constructSTUtil(arr, mid+1, se, st, si*2+2));
    return st[si];
}

/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
long long *constructST(long long arr[], long long n)
{
    // Allocate memory for segment tree

    //Height of segment tree
    long long x = (long long)(ceil(log2(n)));

    // Maximum size of segment tree
    long long max_size = 2*(long long)pow(2, x) - 1;

    long long *st = new long long[max_size];

    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);

    // Return the constructed segment tree
    return st;
}

/// RMQ end

long long level[MAX];
long long leveltoindex[MAX];
long long level_index = 1;
void make_level(long long r) {
  level[r] = level_index++;
  leveltoindex[level[r]] = r;
  for(long long i=0;i<tree[r].size();i++) {
    long long ch = tree[r][i];
    make_level(ch);
  }
}

void euler_tour(long long r) {
  euler_seq.push_back(level[r]);
  indexleft[r] = euler_seq.size()-1;
  for(long long i=0;i<tree[r].size();i++) {
    long long ch = tree[r][i];
    euler_tour(ch);
    euler_seq.push_back(level[r]);
  }
  //indexright[r] = euler_seq.size()-1;
}

void print_euler() {
  cout << "euler_seq: ";
  for(long long i=0;i<euler_seq.size();i++) {
    printf("%d ",leveltoindex[euler_seq[i]]);
  }
  cout << endl;
}

long long _rmq_array[MAX];
long long* rmq_array;

long long lca(long long s,long long t) {
  if (indexleft[s]>indexleft[t]) {long long temp=s; s=t; t=temp;}
  long long _lca = leveltoindex[RMQ(rmq_array, euler_seq.size(), indexleft[s] ,indexleft[t])];
   return _lca;
}


int main() {
  cin >> N >> M;
  // read graph
  long long s,t;
  for(long long i=1; i<=N-1; i++) {
    cin >> s >> t;
    outgoing[s].push_back(t);
    outgoing[t].push_back(s);
  }

  // make rooted tree
  reset_visited();
  dfs(1); // 1 as root;

  // sum up
  sumup(1,0);
  uptree(1,0,0);


  // construct rmq sequence
  make_level(1);
  euler_tour(1);
  //print_euler();
  //print_tree(1);
  // construct rmq
  for (long long i=0;i<euler_seq.size();i++) {
    _rmq_array[i] = euler_seq[i];
  }
  rmq_array = constructST(_rmq_array, euler_seq.size());


  // solve queries

  for(long long i=0; i<M; i++) {
    cin >> s >> t;
    long long highnode = s; long long lownode = t;
    long long distance = 0;
    if ( depth[s] > depth[t] ) { highnode = t; lownode =s;}

    distance = depth[highnode] - depth[lca(highnode,lownode)] + depth[lownode] - depth[lca(highnode,lownode)];

    //printf("distance  from %d to %d: %d\n",highnode,lownode,distance);


    long long lowsize = subtreesize[lownode];
    long long lowlength = subtreelength[lownode];

    // extract non-lower paths from children of highnode
    long long highlength = subtreelength[highnode];
    long long highsize = subtreesize[highnode];

    if (lca(highnode,lownode) == highnode) {
      //highsize = subtreesize[1] - subtreesize[highnode];
      //highlength = subtreelength[1] - subtreelength[highnode];
      for (long long j=0;j<tree[highnode].size();j++) {
        long long ch = tree[highnode][j];
        if (lca(ch,lownode) == ch) { // low is subtree of ch
          highsize -= subtreesize[ch];
          highlength -= (subtreelength[ch] + subtreesize[ch]);
        }
      }
      highsize += uptreesize[highnode];
      highlength += uptreelength[highnode];
    }


    //printf("hs %d hl %d ls %d ll %d\n",highsize,highlength, lowsize, lowlength);

    /*double Answer = (highsize*lowlength + lowsize*highlength +
      (highsize*lowsize)*distance + (highsize*lowsize))/ (double)(highsize*lowsize);*/
    double Answer =
      lowlength/(double)lowsize + highlength/(double)highsize +
      (double)distance + 1.0;
    cout << std::setprecision(10) << Answer << endl;

    //printf("rmq query from %d to %d: %d\n", indexleft[s],indexleft[t], leveltoindex[RMQ(rmq_array, euler_seq.size(), indexleft[s] ,indexleft[t])] );
  }

  return 0;
}
