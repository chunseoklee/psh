#include <iostream>
#include <cstdio>

using namespace std;

#define MAX 1000001
#define LL long long

LL N,M;
LL _N,_M;

LL l[MAX],ql[MAX];
char c[MAX],qc[MAX];

void print_input() {
 for (LL i=1; i<=N; i++)
  printf("%lld-%c\n",l[i],c[i]);

 for (LL i=1; i<=M; i++)
  printf("q:%lld-%c\n",ql[i],qc[i]);

}

int main() {
  // 1. read input
  cin >> _N >> _M;
  N = 1;
  M = 1;
  for (LL i=1; i<=_N; i++) {
    scanf("%lld-%c",&l[N],&c[N]);
    if ( i != 1 ) {
      if (c[N-1] == c[N])  {
        l[N-1] += l[N]; continue;
      }
    }
    N++;
  }
  N--;

  for (LL i=1; i<=_M; i++) {
    scanf("%lld-%c",&ql[M],&qc[M]);
    if ( i != 1 ) {
      if (c[M-1] == c[M])  {
        l[M-1] += l[M]; continue;
      }
    }
    M++;
  }
  M--;
  print_input();

  return 0;
}
