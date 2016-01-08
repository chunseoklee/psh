#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

#define MAX 100001

#define LL long long

LL N;
LL ar[MAX];
LL arr[MAX];
long long sum[MAX];
LL processed[MAX];
set<LL> onetree;

LL findRight(LL left) {

  for (LL i = left; i <= N-left+1; ++i)
    {
      processed[ar[i]]++;
      if (processed[ar[i]] >= ((sum[ar[i]]+1)/2)) {
        //prLLf("erase in i:%d\n",i);
        onetree.erase(ar[i]);
      }
      if (onetree.size() == 0) {
        return i;
      }
    }

  return N-left+1;
}


LL checkhalf(LL left) {

  if ( N%2!=0 && sum[ar[(N+1)/2]]%2 == 0) {
    return (N+1)/2;
  }

  for (LL i = N/2; i >= left; --i)
    {
      if(ar[i] != ar[N-i+1]) {
        return i;
      }
    }

  return -1;

}


bool checkpalin() {
  for (LL i = N/2; i >= 1; --i)
    {
      if(ar[i] != ar[N-i+1]) {
        return false;
      }
    }

  return true;

}


void getsum(LL left) {
  for (LL i = 1; i <= N; ++i)
    {
      processed[i] = 0;
      sum[i] = 0;
    }
  for (LL i = left; i <= N-left+1; ++i)
    {
      sum[ar[i]]++;
    }
}

bool makezeromap(LL left) {
  onetree.clear();
  LL countsizeodd=0;
  for (LL i = 1; i <= N; ++i)
    {
      if( sum[i] >= 1 ) {
        onetree.insert(i);
      }
      if( (sum[i] % 2) != 0) {
        countsizeodd++;
      }
    }

  if (countsizeodd > 1 || (countsizeodd == 1 && N%2 == 0)) {
    return false;
  }
  return true;
}

// [a,b] cap [c,d]

int main(int argc, char *argv[])
{
  /////// 1. input
  cin >> N;
  for (LL i = 1; i <= N; ++i)
    {
      cin >> ar[i];
    }
  ////////

  if (checkpalin()) {
    cout << (N*(N+1))/2  << endl;
    return 0;
  }


  LL left = 1;

  while(ar[left] == ar[N-left+1] && left <= (N-left+1) ) {  left++;  }
  getsum(left);

  if (makezeromap(left) == false) {
    cout << 0 << endl;
    return 0;
  }

  LL right = findRight(left);

  if (right <= (N+1)/2) {
    right = checkhalf(left);
  }

  ///////////////////
  LL left2=1;
  for (LL i = 1; i <= N; ++i)
    {
      arr[N-i+1] = ar[i];
    }

  for (LL i = 1; i <= N; ++i)
    {
      ar[i] = arr[i];
      //prLLf("i: %d ar[i]: %d \n",i,ar[i]);
    }


  while(ar[left2] == ar[N-left2+1] && left <= (N-left2+1) ) {  left2++;  }
  getsum(left2);
  if (makezeromap(left2) == false) {
    cout << 0 << endl;
    return 0;
  }

  LL right2 = findRight(left2);

  if (right2 <= (N+1)/2) {
    right2 = checkhalf(left2);
  }


  long long sum=0;
  if (left == N-right2+1 && right == N-left2+1) {
    sum = left*(N-right+1);
  }
  else {
    sum =  left*(N-right+1) + left2*(N-right2+1) -2;
    if (left == 1 && left2 == 1) {
      sum++;
    }
  }

  /*if (left == 1 && right == N){
    sum = 1;
    }*/

  printf("l1: %d, r1: %d\n",left, right);
  printf("l2: %d, r2: %d\n",left2, right2);

  cout << sum << endl;

  return 0;
}
