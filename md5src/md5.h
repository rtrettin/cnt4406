/*
Portions of this implementation have been adopted from RFC1321
written in C language and are licensed as follows

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.
 
License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.
 
License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.
 
RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.
 
These notices must be retained in any copies of any part of this
documentation and/or software.



*/

#include <cstring>
#include <iostream>

using namespace std;

class MD5
{
public:

  MD5();
  MD5(const string& plaintext);
  void add_hash(const unsigned char *buf, unsigned int length);
  void add_hash(const char *buf, unsigned int length);
  unsigned char get_digest(unsigned int i);
  MD5& finalize();

private:
  void garble(const unsigned char block[64]);
  static void decode(unsigned int output[], const unsigned char input[], unsigned int len);
  static void encode(unsigned char output[], const unsigned int input[], unsigned int len);
  bool flag;
  unsigned char buffer[64]; // bytes that didn't fit in last 64 byte chunk
  unsigned int count[2];   // 64bit counter for number of bits (lo, hi)
  unsigned int state[4];   // digest so far
  unsigned char digest[16]; // the result
};
