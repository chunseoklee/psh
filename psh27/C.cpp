#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
#define MAX 100001

#define FOR(I,S,T) for(int I=S;I<T;++I)
#define REP(I,N) FOR(I,0,N)


int N,K,P;
int a[MAX];
vector<int> even,odd;
vector<int> evenset[MAX];
vector<int> oddset[MAX];


int main(int argc, char *argv[])
{
  cin >> N >> K >> P;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
  }

  //1. odd, even partiton
  for (int i = 1; i <= N; i++) {
    if (a[i]%2 == 0) {
      even.push_back(a[i]);
    }
    else {
      odd.push_back(a[i]);
    }
  }

  //2. spread out even number to all
  /*for (int i = 0,j=0; i < even.size(); i++,j++) {
    evenset[j%P].push_back(even[i]);
    }*/

  //3. spread out odd number to odd set
  int oddnum = K-P;
  int evennum = P;
  if (odd.size() < oddnum) {
    cout << "NO" << endl;
    return 0;
  } else if ( (odd.size() - oddnum)%2 != 0) {
    cout << "NO" << endl;
    return 0;
  } else if ((odd.size() - oddnum)/2 + even.size() < evennum ) {
    cout << "NO" << endl;
    return 0;
  }


  // fill odd set first and flush remaining odd num to even as pair
  int index_odd=0;
  for (int i = 0; i < oddnum; i++) {
    //cout << "odd insert to oddset:" << odd[index_odd] << endl;
    oddset[i].push_back(odd[index_odd++]);
  }

  int index_evenset=0;
  //cout << "*" << odd.size() << endl;
  for (int i = index_odd; i < odd.size(); i=i+2) {
    //cout << "odd insert to evenset:" << odd[i] << "," << odd[i+1] << endl;
    evenset[index_evenset].push_back(odd[i]);
    evenset[index_evenset++].push_back(odd[i+1]);
  }

  for (int i = index_evenset,j=0; j<even.size(); i++,j++) {
    evenset[i%evennum].push_back(even[j]);
  }


  cout << "YES" << endl;
  for (int i = 0; i < evennum; i++) {
    cout << evenset[i].size() << " ";
    for (int j = 0; j < evenset[i].size(); j++) {
      cout << evenset[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < oddnum; i++) {
    cout << oddset[i].size() << " ";
    for (int j = 0; j < oddset[i].size(); j++) {
      cout << oddset[i][j] << " ";
    }
    cout << endl;
  }


  return 0;
}
