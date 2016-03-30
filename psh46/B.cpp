#include <iostream>
#include <cstdio>

using namespace std;

#define MAX 1000001
#define LL long long

LL N,M;
LL _N,_M;

LL l[MAX],patternl[MAX];
char text[MAX],pattern[MAX];

char overlap[MAX];
//char pattern[MAX];


void print_input() {
 for (LL i=0; i<N; i++)
  printf("%lld-%c\n",l[i],text[i]);

 for (LL i=0; i<M; i++)
  printf("q:%lld-%c\n",patternl[i],pattern[i]);

}



int KMP()
{
  int matched_count = 0;

  int j = 0;
  for (int i = 0; i < N; i++)
    for (;;) {      // loop until break
      if (text[i] == pattern[j]) { // matches?
        j++;        // yes, move on to next state
        if (j == M) {   // maybe that was the last state
          matched_count++;
          j = overlap[j];
        }
        break;
      } else if (j == 0) break;   // no match in state j=0, give up
      else j = overlap[j];    // try shorter partial match
    }

  return matched_count;
}

void compute_overlap() {
    overlap[0] = -1;
    for (int i = 0; pattern[i] != '\0'; i++) {
      overlap[i + 1] = overlap[i] + 1;
      while (overlap[i + 1] > 0 &&
             (pattern[i] != pattern[overlap[i + 1] - 1]
              || patternl[i] != patternl[overlap[i+1] -1]))
        overlap[i + 1] = overlap[overlap[i + 1] - 1] + 1;
    }
}



int main() {
  // 1. read input
  cin >> _N >> _M;
  N = 0;
  M = 0;
  for (LL i=0; i<_N; i++) {
    scanf("%lld-%c",&l[N],&text[N]);
    if ( i != 0 ) {
      if (text[N-1] == text[N])  {
        l[N-1] += l[N]; continue;
      }
    }
    N++;
  }
  //N--;

  for (LL i=0; i<_M; i++) {
    scanf("%lld-%c",&patternl[M],&pattern[M]);
    if ( i != 0 ) {
      if (pattern[M-1] == pattern[M])  {
        patternl[M-1] += patternl[M]; continue;
      }
    }
    M++;
  }
  //M--;
  print_input();

  compute_overlap();
  cout << "answer:" << KMP() << endl;

  return 0;
}
