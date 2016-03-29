#include <iostream>
#include <cstdio>

using namespace std;

#define MAX 1000001
#define LL long long

LL N,M;
LL l[MAX];
char c[MAX];


int main() {
  // 1. read input
  cin >> N >> M;
  for (LL i=1; i<=N; i++) {
    scanf("%lld-%c",&l[i],&c[i]);
  }

  return 0;
}
