#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int main() {
    unsigned char buffer_size = 100;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    //make sure that memeory was allocated correctly
    if (buffer == NULL){
      printf("Failed to allocate memory\n");
	goto out;
    }
    
 top:
        printf("$ ");
        
        //read input using fgets
        if (fgets(buffer, buffer_size, stdin) != NULL) {
	 // Manually check if input is longer than the buffer size
         unsigned int i = 0;
         int is_full = 1;
         for (i = 0; i < buffer_size - 1; i++) {
            if (buffer[i] == '\n') {
              is_full = 0;
              buffer[i] = '\0';  // Replace newline with null terminator
                 break;
            }else if (buffer[i] == '\0') {
              is_full = 0;
                 break;
	    }
	 }

	    if (is_full){
	      char ch;
	      while ((ch = getchar()) != '\n' && ch != EOF){
		;//gets rid of the extra input that wont be tokenized
	      }
              printf("Warning: the input was too long, only the first 100 characters will be tokenized.\n");
            }

	  // manually check if 'exit'
	  if(buffer[0] == 'e' && buffer[1] == 'x' &&buffer[2] == 'i' && buffer[3] == 't' && buffer[4] == '\0'){
	    goto out;
	  }

	  //tokenize the input
	   char **tokens = tokenize(buffer);
	   if(tokens != NULL){
	     print_tokens(tokens);
	     free_tokens(tokens);
		
	   }

        } else {
            printf("Error reading input.\n");
            goto out;
        }
	goto top;
 out:
    //free the memory allocated by the buffer
    free(buffer);
    return 0;
}
