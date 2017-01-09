#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fscrypt.h"

int main()
{
  char s[] = "abcdefghijklmnopqrstu123456789";
  //char s[] = "hello world";
  //char s[] = "1234";
  char *outbuf, *recvbuf;
  char pass[] = "abcdefg";
  int len = 0;
  int recvlen = 0;

  
  outbuf = (char *) fs_encrypt((void *) s, strlen(s)+1, pass, &len);
  printf("%s %d\n", "length after encryption = ", len);

  int i = 0;
  printf("ciphertext = ");
  for (i = 0; i < len; i++)
      printf("%02x", outbuf[i]);
  printf("\n");

  recvbuf  = (char *) fs_decrypt((void *) outbuf, len, pass, &recvlen);
  
    printf("Length of recvbuf is %d",recvlen);
    printf("\nLength of s is %d",strlen(s));

  printf("\nOriginal plaintext is: %s\n",s);
  printf("plaintext = %s\n", recvbuf);
}

