
#include "openssl/blowfish.h"
//#include "/home/av/openssl/usr/include/openssl/blowfish.h"
// encrypt plaintext of length bufsize. Use keystr as the key.
const int BLOCKSIZE = 8;           // Block size for blowfish

extern void *fs_encrypt (void *plaintext, int bufsize, char *keystr,int *resultlen);

// decrypt ciphertext of length bufsize. Use keystr as the key.
extern void *fs_decrypt(void *ciphertext, int bufsize, char *keystr,int *resultlen);
