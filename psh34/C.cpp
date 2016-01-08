#include <cstdio>
#include <iostream>


using namespace std;

int N,Q;

class fwtree {
public:
  fwtree(int v) {
    len = v; c = new int[len+1];
    for (int i = 1; i <= len; ++i){ c[i] = 0; }
  };

  void print() {
    for (int i = 1; i <= len; ++i){ cout << get(i) << " ";} cout << endl;
  };

  void add(int index, int v);
  int sum(int s, int t);
  int sum(int t);
  int get(int s);

  int *c;
  int len;
};

void fwtree::add(int index, int v) {
  while( index <= len) {
    //cout << "i:" << index;
    c[index] += v;
    index += (index & -index);
  }
}

int fwtree::sum(int s, int t) {
  if (s == t) {
    return get(s);
  }
  return sum(t) - sum(s-1);
}

int fwtree::sum(int t) {
  int sum = 0;
  while ( t > 0) {
    sum += c[t];
    t -= (t & -t);
  }
  return sum;
}

int fwtree::get(int s) {
  if (s == 1) {
    return c[1];
  }
  return sum(s) - sum(s-1);
}


fwtree *ft;

bool flipped = false;
int l;
int r;

void fold(int s1, int t1, bool reverse) {
  if (!reverse) {
    //printf("not rever\n");
    for (int i = t1+1,j=t1; j >= s1; ++i,j--)
      {
        ft->add(i,ft->get(j));
      }
  }
  else {
    //printf("rever s1 %d t1 %d\n",s1,t1);
    for (int i = s1-1,j=s1; j <= t1; --i,j++)
      {
        //printf("i: %d j: %d\n",i,j);
        ft->add(i,ft->get(j));
      }
  }

}


void fold(int q1) {
  if (flipped) {
    q1 = r-q1;
  }
  if ( q1 <= (r-l+1)/2) {
    fold(l, l+q1-1, false);
    l = l+q1;
  }
  else {
    fold(l+q1, r, true);
    r = l+q1-1;
    flipped != flipped;
  }
  //ft->print();
}


int getSum(int s, int t) {
  if (flipped) {
    return ft->sum(r-t+1,r-s);
  }
  else {
    //cout << "l:" << l+s << "r:" << l+t-1 << endl;
    return ft->sum(l+s, l+(t-1));
  }
}

int main(int argc, char *argv[])
{
  cin >> N >> Q;
  ft = new fwtree(N);
  l = 1;
  r = N;

  for (int i = 1; i <= N; ++i)
    {
      ft->add(i, 1);

    }

  int qtype,q1,q2;
  for (int i = 0; i < Q; ++i)
    {
      //      cout << i+1;
      cin >> qtype;
      if (qtype == 1) {
        cin >> q1;
        fold(q1);
      }
      else {
        cin >> q1 >> q2;
        cout << getSum(q1,q2) << endl;
      }
    }


  //ft->print();

  return 0;
}
