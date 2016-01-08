#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

char pwd[82][200];
int cur = 0;

void insert(char * buf) {
  int cur_char = 0;
  if ( buf[0] == '/') {
    cur = 0;
  }
  while(buf[cur_char] != NULL) {

  }


}

int main(int argc, char *argv[])
{
  char buf[201];
  int N;
  cin >> N;

  for (int i = 0; i < N; ++i){
    scanf("%s ", buf);
    if (buf[0] == 'c') {
      scanf("%s\n", buf);
      buf[strlen(buf)] == NULL;
      //cout << buf << endl;
      insert(buf);
    }
    else {
      print_pwd();
    }
  }

  return 0;
}
