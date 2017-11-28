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
#include "algo.h"

algo::algo() {};

unsigned int algo::F(unsigned int x, unsigned int y, unsigned int z) {
  return x&y | ~x&z;
}

unsigned int algo::G(unsigned int x, unsigned int y, unsigned int z) {
  return x&z | y&~z;
}

unsigned int algo::H(unsigned int x, unsigned int y, unsigned int z) {
  return x^y^z;
}

unsigned int algo::I(unsigned int x, unsigned int y, unsigned int z) {
  return y ^ (x | ~z);
}

unsigned int algo::shift_left(unsigned int x, int n) {
  return (x << n) | (x >> (32-n));
}

void algo::FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = shift_left(a+ F(b,c,d) + x + ac, s) + b;
}

void algo::GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = shift_left(a + G(b,c,d) + x + ac, s) + b;
}

void algo::HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = shift_left(a + H(b,c,d) + x + ac, s) + b;
}

void algo::II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = shift_left(a + I(b,c,d) + x + ac, s) + b;
}

void algo::decode(unsigned int output[], const unsigned char input[], unsigned int len) //redirects input to output
{
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4)         //an unsigned int is 4 bytes
    output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j+1]) << 8) |  //bitwise or operator with left shifting
      (((unsigned int)input[j+2]) << 16) | (((unsigned int)input[j+3]) << 24);
}

void algo::encode(unsigned char output[], const unsigned int input[], unsigned int len)  //change ints to chars and redirect
{
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {       //encodes unsigned integers into chars (1 byte)
    output[j] = input[i] & 0xff;                                //bitwise and operation with 0xff to determine individual bits
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}

