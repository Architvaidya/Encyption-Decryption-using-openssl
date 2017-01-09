

#include<stdio.h>
#include"openssl/blowfish.h"
#include<stdlib.h>
#include<string.h>
#define SIZE 16
#define IVLENGTH 8

BF_KEY key;

unsigned char *iv;
 



void *fs_encrypt(void *plaintext, int bufsize, char *keystr,int *resultlen)
{
	int i;
	unsigned char *encryption_output;
	encryption_output = (unsigned char *)calloc(2000, sizeof(encryption_output));
	iv = (unsigned char *)calloc(IVLENGTH, sizeof(iv));
	for(i=0;i<IVLENGTH;i++){
		iv[i] = '0';
	}
	
	unsigned char * input=(unsigned char *) plaintext;
	
	 
 	BF_set_key(&key, SIZE, (const unsigned char *)keystr);
	 
        
         
        BF_cbc_encrypt(input, encryption_output,bufsize, &key, iv, BF_ENCRYPT);
	
        
        *resultlen=strlen((const char *)encryption_output);
	return (void *) encryption_output;

}

void *fs_decrypt(void *ciphertext, int bufsize, char *keystr,int *resultlen)
{
	
	int i;
	unsigned char *decryption_output; 
	decryption_output =  (unsigned char *)calloc(100, sizeof(decryption_output));
	iv = (unsigned char *)calloc(IVLENGTH, sizeof(iv));
	for(i=0;i<IVLENGTH;i++){
		iv[i] = '0';
	}
	unsigned char * input=(unsigned char *) ciphertext;
	   
 	
        
                   
       BF_cbc_encrypt(input, decryption_output, bufsize, &key, iv, BF_DECRYPT);      

        
        *resultlen=strlen((const char*) decryption_output);
	return (void *) decryption_output;
}

