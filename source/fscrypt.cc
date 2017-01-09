#include<stdio.h>
#include"openssl/blowfish.h"
#include<stdlib.h>
#include<string.h>
#include"fscrypt.h"
#define IVLENGTH 8
#define SIZE 16



BF_KEY key;

int length_of_plaintext;




char *iv;



void *fs_encrypt(void *plaintext, int bufsize, char *keystr,int *resultlen)
{
	unsigned char *encryption_output;
	encryption_output = (unsigned char *)calloc(2000, sizeof(encryption_output));
	//data.input[] = (unsigned char *)calloc(bufsize,sizeof(data.input));
	//data.input[bufsize];
	unsigned char input[bufsize];
	char xor_value;
	int i,block_iterator,block_pointer,a,tempsize, flag = 0;
        unsigned char *cipher = encryption_output;
	unsigned char * temp=(unsigned char *) plaintext; 
	
	length_of_plaintext = bufsize;
	iv = (char *)calloc(BLOCKSIZE, sizeof(char));
	for(i=0;i<IVLENGTH;i++){
		iv[i] = '0';
	}

        BF_set_key(&key, SIZE, (const unsigned char *)keystr);
	    
          
        for(i=0;i<BLOCKSIZE;i++)
	{
		xor_value = (* temp)^iv[i];
		input[i]=xor_value;  
		temp++;
	
	}
	
	
    
         
	i = 0;	
	bufsize = bufsize - BLOCKSIZE;
	BF_ecb_encrypt(&input[i], encryption_output, &key, BF_ENCRYPT);
	block_pointer = BLOCKSIZE;
	
	//encrypt(bufsize, i, j, temp, input);
	while(bufsize > 0)
	{
		
		block_iterator = 0;
		while(block_iterator<BLOCKSIZE){
			xor_value = (*encryption_output) ^ (* temp);
			input[block_pointer++]= xor_value; 
			encryption_output++;
			temp++;
			block_iterator = block_iterator + 1;
		}
		
		i=i+BLOCKSIZE;  	
		BF_ecb_encrypt(&input[i], encryption_output, &key, BF_ENCRYPT);
	  	bufsize = bufsize - BLOCKSIZE;
	}

	

	
	
        
	*resultlen=  strlen((const char *)cipher);
	return (void *) cipher;

}

void *fs_decrypt(void *ciphertext, int bufsize, char *keystr,int *resultlen)
{	
	unsigned char *decryption_out ;
	decryption_out = (unsigned char *)calloc(2000, sizeof(decryption_out));
	int i,j,k,block_iterator;
	char xor_value;
	unsigned char plaintext_buffer[length_of_plaintext];
        //unsigned char plaintext_buffer[bufsize+1];
        
	unsigned char *pointer_to_buffer;
	pointer_to_buffer = (unsigned char *)calloc(bufsize+1, sizeof(pointer_to_buffer));
	pointer_to_buffer = plaintext_buffer;
        unsigned char * input=(unsigned char *) ciphertext;
	unsigned char * pointer_to_cipher=(unsigned char *) ciphertext;
	unsigned char *finalplain = decryption_out; 
	
	iv = (char *)calloc(BLOCKSIZE, sizeof(char));
	for(i=0;i<IVLENGTH;i++){
		iv[i] = '0';
	}   
 
          	          
        BF_ecb_encrypt(input, decryption_out, &key, BF_DECRYPT);

       
        for(k=0;k<BLOCKSIZE;k++)
        {
          xor_value = (*decryption_out)^iv[k];
          plaintext_buffer[k]= xor_value;
          
          
	  decryption_out++;        
	}
	
        
         j=0;
         i=BLOCKSIZE;
         int counter = 0; 
	 bufsize = bufsize - BLOCKSIZE;
	 //printf("\nLength of decryption_out is %d\n",strlen(decryption_out));
         while(bufsize>0)
		{              
			input = input + BLOCKSIZE;
			BF_ecb_encrypt(input, decryption_out, &key, BF_DECRYPT);
			block_iterator = 0;
			while(block_iterator<BLOCKSIZE){
				xor_value = (*pointer_to_cipher) ^ (*decryption_out);
				plaintext_buffer[i]=xor_value;
				//printf("\n%d-->%c\n",i,plaintext_buffer[i]);
                          	decryption_out++;
			  	pointer_to_cipher++;
				block_iterator = block_iterator + 1;
				i = i + 1;
				j = j + 1;
				counter++;
				
			}
                   	 
			bufsize = bufsize - BLOCKSIZE;
	        }

        

	          
 	*resultlen=strlen((const char*) plaintext_buffer);
 	
	return (void *) pointer_to_buffer;
}

