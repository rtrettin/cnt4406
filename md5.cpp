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

#include "md5.h"
#include "algo.h"

MD5::MD5()
{
  count[0] = 0;
  count[1] = 0;
  state[0] = 0x67452301;  //initialization constants
  state[1] = 0xefcdab89;
  state[2] = 0x98badcfe;
  state[3] = 0x10325476;

  flag = false;

}

MD5::MD5(const std::string &plaintext)
{
  count[0] = 0;
  count[1] = 0;
  state[0] = 0x67452301;  //initialization constants
  state[1] = 0xefcdab89;
  state[2] = 0x98badcfe;
  state[3] = 0x10325476;

  flag = false;

  add_hash(plaintext.c_str(), plaintext.length()); //add hash value to table
  finalize();
}

   //MD5 algorithm, Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All rights reserved.

unsigned char MD5::get_digest(unsigned int i)
{
  return digest[i];
}

void MD5::garble(const unsigned char block[64])
{
  algo func_a;

  unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];
  func_a.decode (x, block, 64);


  /* Round 1 */
  func_a.FF (a, b, c, d, x[ 0], 7, 0xd76aa478); /* 1 */
  func_a.FF (d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
  func_a.FF (c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
  func_a.FF (b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
  func_a.FF (a, b, c, d, x[ 4], 7, 0xf57c0faf); /* 5 */
  func_a.FF (d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
  func_a.FF (c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
  func_a.FF (b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
  func_a.FF (a, b, c, d, x[ 8], 7, 0x698098d8); /* 9 */
  func_a.FF (d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
  func_a.FF (c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
  func_a.FF (b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
  func_a.FF (a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
  func_a.FF (d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
  func_a.FF (c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
  func_a.FF (b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

  /* Round 2 */
  func_a.GG (a, b, c, d, x[ 1], 5, 0xf61e2562); /* 17 */
  func_a.GG (d, a, b, c, x[ 6], 9, 0xc040b340); /* 18 */
  func_a.GG (c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
  func_a.GG (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
  func_a.GG (a, b, c, d, x[ 5], 5, 0xd62f105d); /* 21 */
  func_a.GG (d, a, b, c, x[10], 9,  0x2441453); /* 22 */
  func_a.GG (c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
  func_a.GG (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
  func_a.GG (a, b, c, d, x[ 9], 5, 0x21e1cde6); /* 25 */
  func_a.GG (d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
  func_a.GG (c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
  func_a.GG (b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
  func_a.GG (a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
  func_a.GG (d, a, b, c, x[ 2], 9, 0xfcefa3f8); /* 30 */
  func_a.GG (c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
  func_a.GG (b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  func_a.HH (a, b, c, d, x[ 5], 4, 0xfffa3942); /* 33 */
  func_a.HH (d, a, b, c, x[ 8], 11, 0x8771f681); /* 34 */
  func_a.HH (c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
  func_a.HH (b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
  func_a.HH (a, b, c, d, x[ 1], 4, 0xa4beea44); /* 37 */
  func_a.HH (d, a, b, c, x[ 4], 11, 0x4bdecfa9); /* 38 */
  func_a.HH (c, d, a, b, x[ 7], 16, 0xf6bb4b60); /* 39 */
  func_a.HH (b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
  func_a.HH (a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
  func_a.HH (d, a, b, c, x[ 0], 11, 0xeaa127fa); /* 42 */
  func_a.HH (c, d, a, b, x[ 3], 16, 0xd4ef3085); /* 43 */
  func_a.HH (b, c, d, a, x[ 6], 23,  0x4881d05); /* 44 */
  func_a.HH (a, b, c, d, x[ 9], 4, 0xd9d4d039); /* 45 */
  func_a.HH (d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
  func_a.HH (c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
  func_a.HH (b, c, d, a, x[ 2], 23, 0xc4ac5665); /* 48 */

  /* Round 4 */
  func_a.II (a, b, c, d, x[ 0], 6, 0xf4292244); /* 49 */
  func_a.II (d, a, b, c, x[ 7], 10, 0x432aff97); /* 50 */
  func_a.II (c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
  func_a.II (b, c, d, a, x[ 5], 21, 0xfc93a039); /* 52 */
  func_a.II (a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
  func_a.II (d, a, b, c, x[ 3], 10, 0x8f0ccc92); /* 54 */
  func_a.II (c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
  func_a.II (b, c, d, a, x[ 1], 21, 0x85845dd1); /* 56 */
  func_a.II (a, b, c, d, x[ 8], 6, 0x6fa87e4f); /* 57 */
  func_a.II (d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
  func_a.II (c, d, a, b, x[ 6], 15, 0xa3014314); /* 59 */
  func_a.II (b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
  func_a.II (a, b, c, d, x[ 4], 6, 0xf7537e82); /* 61 */
  func_a.II (d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
  func_a.II (c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /* 63 */
  func_a.II (b, c, d, a, x[ 9], 21, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  // Zeroize sensitive information.
  memset(x, 0, sizeof x);
}


// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::add_hash(const unsigned char input[], unsigned int length)
{
  // compute number of bytes mod 64
  unsigned int index = count[0] / 8 % 64;

  // Update number of bits
  if ((count[0] += (length << 3)) < (length << 3))
    count[1]++;
  count[1] += (length >> 29);

  // number of bytes we need to fill in buffer
  unsigned int firstpart = 64 - index;

  unsigned int i;

  // transform as many times as possible.
  if (length >= firstpart)
  {
    // fill buffer first, transform
    memcpy(&buffer[index], input, firstpart);
    garble(buffer);

    // transform chunks of blocksize (64 bytes)
    for (i = firstpart; i + 64 <= length; i += 64)
      garble(&input[i]);

    index = 0;
  }
  else
    i = 0;

  // buffer remaining input
  memcpy(&buffer[index], &input[i], length-i);
}

// for convenience provide a verson with signed char
void MD5::add_hash(const char input[], unsigned int length)
{
  add_hash((const unsigned char*)input, length);
}

// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5& MD5::finalize()
{
  algo func_b;

  static unsigned char padding[64];
  padding[0] = 0x80;
  for(int i =1; i < 64; i++)
	padding[i] = 0;

  if (!flag) {
    // Save number of bits
    unsigned char bits[8];
    func_b.encode(bits, count, 8);

    // pad out to 56 mod 64.
    unsigned int index = count[0] / 8 % 64;
    unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);
    add_hash(padding, padLen);

    // Append length (before padding)
    add_hash(bits, 8);

    // Store state in digest
    func_b.encode(digest, state, 16);

    // Zeroize sensitive information.
    memset(buffer, 0, sizeof buffer);
    memset(count, 0, sizeof count);

    flag=true;
  }
 
  return *this;
}
