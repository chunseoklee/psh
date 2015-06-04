#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <assert.h>
#include <cstdio>
using namespace std;

#define MAX 100000

struct _city {
  _city(){}
  _city(float x_,float y_){x=x_; y=y_;}
  float x;
  float y;
};
typedef _city city;
vector<city> cities;
vector<city> cities_x;
vector<city> cities_y;


int N;
//city cities[MAX+1];
//city cities_by_x[MAX+1];
//city cities_by_y[MAX+1];
vector< int* > perm;
vector<int> king;



void print_cities(vector<city> cities)
{
  for (int i=0; i < cities.size(); i++) {
    cout << cities[i].x << "," << cities[i].y << endl;
  }
  /*for (int i=0; i < 9; i++) {
    cout <<  "king: " << king[i] << endl;
    }*/

}

bool cmp_by_x(const city& lhs, const city& rhs)
{
  return lhs.x < rhs.x;
}

bool cmp_by_y(const city& lhs, const city& rhs)
{
  return lhs.y < rhs.y;
}

struct Node;
int count_in_range(Node* node, float* xrange, float* yrange );




////////////////////////////////////////
////// range-tree ////////

struct Node {

Node():nofpoints(0), isleaf(false){}

  Node* left;
  Node* right;
  Node* nodey;

  vector<city> clist;

  int nofpoints;
  float key;
  bool isleaf;
};

bool issame(vector<city> clist)
{
  /*for(int i=0;i<clist.size()-1;i++){
    if(clist[i].x !=  clist[i+1].x)
      return false;
      }*/
  int mid = (clist.end()-clist.begin())/2;
  nth_element(clist.begin(), clist.begin()+mid, clist.end(), cmp_by_x);
  if(clist[mid].x == clist[clist.size()-1].x){
    return true;
  }
  else
    return false;

}

bool issame_y(vector<city> clist)
{
  /*for(int i=0;i<clist.size()-1;i++){
    if(clist[i].x !=  clist[i+1].x)
      return false;
      }*/
  int mid = (clist.end()-clist.begin())/2;
  nth_element(clist.begin(), clist.begin()+mid, clist.end(), cmp_by_y);
  if(clist[mid].y == clist[clist.size()-1].y){
    return true;
  }
  else
    return false;

}

void construct_y(Node* node, vector<city> clist);

void construct(Node* node, vector<city> clist)
{
  if(clist.size() < 2){
    node->isleaf = true;
    if(clist.size() !=0){
      node->nofpoints = 1;
      node->clist.push_back(clist[0]);

    }
    else{
      node->nofpoints = 0;
    }
    node->nodey = new Node();
    construct_y(node->nodey, node->clist);
    return;
  }
  if(issame(clist)){
    node->isleaf = true;
    node->nofpoints = clist.size();
    (node->clist).resize(node->nofpoints);
    //sort(clist.begin(),clist.end(), cmp_by_y);
    copy(clist.begin(), clist.end(), (node->clist).begin());
    node->nodey = new Node();
    construct_y(node->nodey, node->clist);
    return;
  }

  int mid = (clist.end()-clist.begin())/2;
  nth_element(clist.begin(), clist.begin()+mid, clist.end(), cmp_by_x);
  node->key = clist[mid].x + 0.5;

  node->nofpoints = clist.size();
  (node->clist).resize(node->nofpoints);

  copy(clist.begin(), clist.end(), (node->clist).begin());


  node->nodey = new Node();
  construct_y(node->nodey, node->clist);

  vector<city> left;
  vector<city> right;

  for(int i=0;i<clist.size();i++){
    if(clist[i].x < node->key){
      left.push_back(clist[i]);
    }
    else{
      right.push_back(clist[i]);
    }
  }

  //cout << " key: " << node->key << endl;
  //cout << " left s: " << left.size() << endl;
  //print_cities(left);
  //cout << " right s: " << right.size() << endl;
  //print_cities(right);
  node->left = new Node();
  construct(node->left,left);
  node->right = new Node();
  construct(node->right,right);

}

void construct_y(Node* node, vector<city> clist)
{
  if(clist.size() < 2){
    node->isleaf = true;
    if(clist.size() !=0){
      node->nofpoints = 1;
      node->clist.push_back(clist[0]);
    }
    else{
      node->nofpoints = 0;
    }
    return;
  }
  if(issame_y(clist)){
    node->isleaf = true;
    node->nofpoints = clist.size();
    (node->clist).resize(node->nofpoints);
    //sort(clist.begin(),clist.end(), cmp_by_y);
    copy(clist.begin(), clist.end(), (node->clist).begin());
    return;
  }

  int mid = (clist.end()-clist.begin())/2;
  nth_element(clist.begin(), clist.begin()+mid, clist.end(), cmp_by_y);
  node->key = clist[mid].y + 0.5;
  node->nofpoints = clist.size();
  // node->clist = clist;
  (node->clist).resize(node->nofpoints);
  copy(clist.begin(), clist.end(), (node->clist).begin());

  vector<city> left;
  vector<city> right;

  for(int i=0;i<clist.size();i++){
    if(clist[i].y < node->key){
      left.push_back(clist[i]);
    }
    else{
      right.push_back(clist[i]);
    }
  }


  node->left = new Node();
  construct_y(node->left,left);
  node->right = new Node();
  construct_y(node->right,right);

}


void print_tree(Node* node)
{
  if(node->isleaf){
    cout << "Leaf node\n";
    cout << "nofpoints: " << node->nofpoints << endl;
    print_cities(node->clist);
    return;
  }
  cout << "Non-Leaf node\n";
  cout << "key:" << node->key << endl;
  cout << "nofpoints: " << node->nofpoints << endl;
  print_cities(node->clist);

  cout << "left child\n";
  print_tree(node->left);
  cout << "right child\n";
  print_tree(node->right);

}

void print_ytree(Node* node)
{
  if(node->isleaf){
    cout << "Leaf node\n";
    print_tree(node->nodey);
    return;
  }
  cout << "Non-Leaf node\n";
  print_tree(node->nodey);

  cout << "left child\n";
  print_ytree(node->left);
  cout << "right child\n";
  print_ytree(node->right);

}
/////////////////////////////////////


Node* get_splitnode(Node* node, float* range)
{
  Node* curnode = node;
  while(!curnode->isleaf){
    if(curnode->key > range[0] && curnode->key < range[1]){
      return curnode;
    }
    else if(curnode->key > range[0] && curnode->key > range[1]) {
      curnode = curnode->left;
    }
    else{
      curnode = curnode->right;
    }
  }
  return curnode;
}

int count_leafy(vector<city> clist, float* yrange);

int count_in_y(Node* node, float* yrange )
{
  Node* splitnode = get_splitnode(node,yrange);
  /*if(splitnode->isleaf){
    cout << "split is leaf\n";
  }
  else {
    cout << "split is non-leaf\n";
    }
    print_cities(splitnode->clist);*/

  if (splitnode->isleaf) {
    return count_leafy(splitnode->clist,yrange);
  }

  int sum = 0;
  Node* curnode;
  //1.left path
  curnode = splitnode->left;
  while (!curnode->isleaf) {
    if(curnode->key > yrange[0]){
      sum += curnode->right->nofpoints;
      curnode = curnode->left;
    }
    else{
      curnode = curnode->right;
    }
  }
  sum += count_leafy(curnode->clist,yrange);

  //2. right path
  curnode = splitnode->right;
  while (!curnode->isleaf) {
    if(curnode->key < yrange[1]){
      sum +=  curnode->left->nofpoints;
      curnode = curnode->right;
    }
    else{
      curnode = curnode->left;
    }
  }
  sum += count_leafy(curnode->clist,yrange);

  return sum;

}

int count_leafy(vector<city> clist, float* yrange)
{
  int sum =0;
  for(int i=0;i<clist.size();i++){
    if(clist[i].y > yrange[0] && clist[i].y < yrange[1]){
      sum++;
    }

  }

  //cout << "lieaf " << sum << endl;
  return sum;

}

void swap(int* str, int i, int j)
{
    int temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}



void print_perm()
{
  for(int i=0;i<perm.size();i++){
    for(int j=0;j<9;j++){
      printf("%d ", perm[i][j]);
    }
    cout << endl;
  }

}

void print_array(int *ar)
{
    for(int j=0;j<9;j++){
      printf("%d ", ar[j]);
    }
    cout << endl;
}


void permute(int *string, int start, int end)
{
    if(start == end)
    {
      int* temp = new int[9];
      for(int i=0;i<9;i++){
        temp[i] = string[i];
      }
      //cout << endl;
      //print_array(temp);
      perm.push_back(temp);
      return;
    }

    permute(string, start + 1, end);
    int i;
    for(i = start + 1; i < end; i++)
    {
        if(string[start] == string[i])
            continue;
        swap(string, start, i);
        permute(string, start + 1, end);
        swap(string, start, i);
    }
}

int count_in_range(Node* node, float* xrange, float* yrange )
{
  Node* splitnode = get_splitnode(node,xrange);
  /*if(splitnode->isleaf){
    cout << "split is leaf\n";
  }
  else {
    cout << "split is non-leaf\n";
    }
    print_cities(splitnode->clist);*/

  if (splitnode->isleaf) {
    return count_in_y(splitnode->nodey, yrange);
  }

  int sum = 0;
  Node* curnode;
  //1.left path
  curnode = splitnode->left;
  while (!curnode->isleaf) {
    if(curnode->key > xrange[0]){
      sum += count_in_y(curnode->right->nodey, yrange);
      curnode = curnode->left;
    }
    else{
      curnode = curnode->right;
    }
  }
  sum += count_in_y(curnode->nodey,yrange);

  //2. right path
  curnode = splitnode->right;
  while (!curnode->isleaf) {
    if(curnode->key < xrange[1]){
      sum += count_in_y(curnode->left->nodey,yrange);
      curnode = curnode->right;
    }
    else{
      curnode = curnode->left;
    }
  }
  sum += count_in_y(curnode->nodey,yrange);

  return sum;

}




Node* root = new Node();


//     x0  x1
//   0 | 3 |  6
// y1----------
//   1 | 4 |  7
// y0----------
//   2 | 5 |  8
//
bool is_valid(int* f9 )
{

  int sum_x0 = king[f9[0]] + king[f9[1]] + king[f9[2]];

  int i_x0 = sum_x0-1; // x-axis start index in cities
  float x0 = cities_x[i_x0].x + 0.5;            // x0 value

  int sum_x1 = king[f9[3]] + king[f9[4]] + king[f9[5]] + sum_x0;

  int i_x1 = sum_x1-1; // x-axis start index in cities
  float x1 = cities_x[i_x1].x + 0.5;            // x0 value

  int sum_y0 = king[f9[2]] + king[f9[5]] + king[f9[8]];

  int i_y0 = sum_y0-1; // x-axis start index in cities
  float y0 = cities_y[i_y0].y + 0.5;            // x0 value

  int sum_y1 = king[f9[1]] + king[f9[4]] + king[f9[7]] + sum_y0;

  int i_y1 = sum_y1-1; // x-axis start index in cities
  float y1 = cities_y[i_y1].y + 0.5;            // x0 value


  // 0 check
  float xrange[2];
  xrange[0] = -2000000000;
  xrange[1] = x0;
  float yrange[2];
  yrange[0] = y1;
  yrange[1] = 2000000000;
  if(count_in_range(root,xrange,yrange) != king[f9[0]])
    return false;

// 3 check
  //float xrange[2];
  xrange[0] = x0;
  xrange[1] = x1;
  //float yrange[2];
  yrange[0] = y1;
  yrange[1] = 2000000000;
  if(count_in_range(root,xrange,yrange) != king[f9[3]])
    return false;


 // 6 check
  //float xrange[2];
  xrange[0] = x1;
  xrange[1] = 2000000000;
  //float yrange[2];
  yrange[0] = y1;
  yrange[1] = 2000000000;
  if(count_in_range(root,xrange,yrange) != king[f9[6]])
    return false;

  // 2 check
  //float xrange[2];
  xrange[0] = -2000000000;
  xrange[1] = x0;
  //float yrange[2];
  yrange[0] = -2000000000;
  yrange[1] = y0;
  if(count_in_range(root,xrange,yrange) != king[f9[2]])
    return false;

 // 5 check
  //float xrange[2];
  xrange[0] = x0;
  xrange[1] = x1;
  //float yrange[2];
  yrange[0] = -2000000000;
  yrange[1] = y0;
  if(count_in_range(root,xrange,yrange) != king[f9[5]])
    return false;


  // 8 check
  //float xrange[2];
  xrange[0] = x1;
  xrange[1] = 2000000000;
  //float yrange[2];
  yrange[0] = -2000000000;
  yrange[1] = y0;
  if(count_in_range(root,xrange,yrange) != king[f9[8]])
    return false;



  cout << x0 << " " << x1 << endl;
  cout << y0 << " " << y1 << endl;
  return true;
}

bool solve()
{

  for(int i=0;i<perm.size();i++){
    if(is_valid(perm[i])){
      return true;
    }

  }

  return false;
}


int main(int argc, char *argv[])
{
  cin >> N;
  for (int i=1; i <= N; i++) {
    int temp_x, temp_y;
    cin >> temp_x >> temp_y;
    cities.push_back(city(temp_x,temp_y));
  }
  //int mid = (cities.end()-cities.begin())/2;
  //nth_element(cities.begin(), cities.begin()+mid, cities.end(), cmp_by_y);
  //cout << cities[mid].x << "," << cities[mid].y << endl;

  construct(root, cities);

  //print_tree(root);

  float xrange[2] = { 1.5 , 3.5 };
  float yrange[2] = { 1.5 , 3.5 };
  cout << count_in_range(root, xrange, yrange);

  for (int i=0; i < 9; i++) {
    int temp;
    cin >> temp;
    king.push_back(temp);
  }

  cities_x.resize(cities.size());
  copy(cities.begin(),cities.end(), cities_x.begin());
  sort(cities_x.begin(),cities_x.end(), cmp_by_x);

  cities_y.resize(cities.size());
  copy(cities.begin(),cities.end(), cities_y.begin());
  sort(cities_y.begin(),cities_y.end(), cmp_by_y);

  //print_cities(cities_x);
  //print_cities(cities_y);

  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  permute(arr, 0, 9);

  //cout << perm.size();
  //print_perm();
  if(!solve()){
    cout << -1 << endl;
  }

  return 0;
}
