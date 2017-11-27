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

#include <iostream>

  class algo {
  public:
  algo();
  unsigned int shift_left(unsigned int x, int n);
  unsigned int F(unsigned int x, unsigned int y, unsigned int z);
  unsigned int G(unsigned int x, unsigned int y, unsigned int z);
  unsigned int H(unsigned int x, unsigned int y, unsigned int z);
  unsigned int I(unsigned int x, unsigned int y, unsigned int z);
  void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  static void decode(unsigned int output[], const unsigned char input[], unsigned int len);
  static void encode(unsigned char output[], const unsigned int input[], unsigned int len);
};
