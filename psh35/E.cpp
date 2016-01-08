#include <iostream>
#include <cstdio>
#include <set>


using namespace std;

#define MAX 100001
#define LL long long

LL N;
LL input[MAX];
LL ar[MAX];
LL sum[MAX];
LL processed[MAX];
set<LL> tree;


bool isPalindrome(LL* a) {
  for (int i = N/2; i >= 1; --i)
    if(a[i] != a[N-i+1])
      return false;
  return true;
}


void resetSum() {
  for (int i = 0; i < MAX; ++i) { sum[i] = 0; processed[i] = 0; }
}


void computeSum(int left) {
  resetSum();
  for (int i = left; i <= N-left+1; ++i) {
    sum[ar[i]]++;
  }

}


void computeTree() {
  tree.clear();

  for (int i = 1; i < MAX; ++i) {
    if (sum[i]>0) {
      tree.insert(i);
      if (N==90767)
        printf("i:%d sum: %d\n",i,sum[i]);
    }
  }
}


bool isRearrangable(LL* a) {
  int c[MAX];
  for (int i = 1; i <= N; ++i) c[i] = 0;

  for (int i = 1; i <= N; ++i) c[a[i]]++;

  int odd=0;
  for (int i = 1; i <= N; ++i)
    if(c[i] % 2 !=0) {
      odd++;
    }

  if (odd > 1) return false;
  if (odd == 1 && N%2 == 0) return false;

  return true;
}


int AdjustRight(int right) {

  if (N%2!=0 && right == (N+1)/2 &&
      sum[ar[right]]%2 == 0  ) return right;

  for (int i = right; i >= 1; --i) {
    if (ar[i] != ar[N-i+1]) {
      return i;
    }
  }
  return -1;
}


int computeRight(int left) {

  for (int i = left; i <= N-left+1; ++i) {
    int v = ar[i];
    processed[v]++;
    if ( processed[v] >= ((sum[v]+1)/2) ) {
      tree.erase(v);
    }
    if (tree.size() == 0) {
      if ( i <= (N+1)/2 ) {
        return AdjustRight(i);
      }
      return i;
    }
  }
  return -1;

}


void findMinterm(LL* a, LL* out,bool reverse) {
  //1. reverse check
  if (reverse) for (int i = 1; i <= N; ++i) ar[N-i+1] = a[i];
  else for (int i = 1; i <= N; ++i) ar[i] = a[i];

  //2. find first left diff
  int left = 1;
  while(ar[left] == ar[N-left+1] && left != (N-left+1)) { left++; }

  int right = N-left+1;

  computeSum(left);
  computeTree();
  right = computeRight(left);

  // output
  if(reverse) { out[0] = N-right+1; out[1] = N-left+1; }
  else { out[0] = left; out[1] = right; }

  if (N==90767)
    printf("l:%d r:%d\n",left,right);
}


int main(int argc, char *argv[])
{
  //1. input
  cin >> N;
  for (LL i = 1; i <= N; ++i) cin >> input[i];

  //2. if input is palindrome, exit.
  if (isPalindrome(input)) {
    cout << (N*(N+1))/2  << endl;
    return 0;
  }
  if (!isRearrangable(input)) {
    cout << 0 << endl;
    return 0;
  }

  // 3-1
  LL term1[2];
  findMinterm(input, term1, false);
  // 3-2
  LL term2[2];
  findMinterm(input, term2, true);

  //4. term duplication removal
  LL s1 = term1[0]; LL t1 = term1[1];
  LL s2 = term2[0]; LL t2 = term2[1];

  LL ret = 0;
  if (s1 == s2 && t1 == t2) {
    ret = s1*(N-t1+1);
  } else {
    ret = s1*(N-t1+1) + s2*(N-t2+1) - 2;
    if (s1 == 1 && t2 == N) {
      ret++;
    }
  }

  cout << ret << endl;

  return 0;
}
