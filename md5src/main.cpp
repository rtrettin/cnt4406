#include <iostream>
#include "md5.h"
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    MD5 hashed_str = MD5(argv[1]);

  char buf[33];
  for (int i=0; i<16; i++)
    sprintf(buf+i*2, "%02x", hashed_str.get_digest(i));
  buf[32]=0;

    cout << string(buf)  << endl;

    return 0;
}
