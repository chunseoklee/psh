#include <iostream>
#include <cstdio>

using namespace std;

#define LL long long
#define MAX 200001

LL N;
LL a[MAX];
LL sum[MAX];
LL productsum;
struct Line{
  LL a, b, get(LL x) { return a*x + b;}
};

// lines should be inserted in decreasing slope order.
class upperEnvelope {
public:
  upperEnvelope() {size=0;}
  Line envelope[MAX];
  LL size;
  LL search(LL x);
  void add(LL slope, LL intercept);
  bool isNotValid(LL, LL, LL);
};

LL upperEnvelope::search(LL x) {
  LL s,t,m;
  s = -1; t = size-1;
  while (t-s > 1) {
    m=(s+t)/2;
    //printf("before s %lld m %lld t %lld\n",s,m,t);
    if (envelope[m].get(x) >= envelope[m+1].get(x)) {
      t = m;
    }
    else {
      s = m;
    }
    //printf("end s %lld m %lld t %lld\n",s,m,t);
  }

  //printf("search for %lld is index %lld\n",x,t);
  return envelope[t].get(x);
};

bool upperEnvelope::isNotValid(LL p3, LL p2, LL p1) {
  bool flag = false;

  Line l3 = envelope[p3], l2 = envelope[p2] , l1 = envelope[p1];

  //LL diff = (l2.b - l3.b)*(l1.a) + (l3.a - l2.a)*(l1.b) -
  //  (l2.b - l3.b)*(l3.a) + (l3.a - l2.a)*(l3.b) ;

  LL diff = (l1.b-l2.b)*(l3.a-l2.a) - (l2.b-l3.b)*(l2.a-l1.a);

  if (diff >= 0) { flag = true; }
  return flag;
}

// added in slope decreasing order.
void upperEnvelope::add(LL slope, LL intercept) {
  envelope[size++] = (Line){slope,intercept};
  while ( size > 2 && isNotValid(size-3, size-2, size-1)) {
    envelope[size-2] = envelope[size-1], size--;
  }
}

upperEnvelope ue;

int main() {
  cin >> N;
  // 1. read input;
  for (LL i=1;i<=N;i++) cin >> a[i];

  // 2. compute sum
  a[0] = 0;
  sum[0] = 0;
  productsum = 0;
  for (LL i=1;i<=N;i++){
    sum[i] = sum[i-1] + a[i];
    productsum += a[i]*i;
  }

  LL max_diff = 0;
  // 3. [a_l, a_(l+1), ...., a_r] to [a_(l+1), .... a_r, a_l]
  ue.size=0;
  for (LL l=N-1;l>=1;l--) {
    ue.add(l+1,-sum[l+1]);
    LL search_result = ue.search(a[l]);
    LL diff = search_result + sum[l] -  a[l]*l;
    //printf("l: %lld ue size: %lld search: %lld diff %lld\n",l,ue.size,search_result,diff);
    if (max_diff < diff) max_diff = diff;
  }



  // 4. [a_l, a_(l+1), ...., a_r] to [a_r, a_l, ...., a_r-1]
  ue.size = 0;
  for (LL r=2;r<=N;r++) {
    ue.add(1-r,-sum[r-2]);
    LL search_result = ue.search(-a[r]);
    LL diff = search_result + sum[r-1] -  a[r]*r;
    //printf("l: %lld ue size: %lld search: %lld diff %lld\n",l,ue.size,search_result,diff);
    if (max_diff < diff) max_diff = diff;
  }

  cout << productsum + max_diff << endl;

  return 0;
}
