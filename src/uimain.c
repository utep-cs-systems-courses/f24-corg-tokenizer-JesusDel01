#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

//function to turn string into int
char turn_to_int(const char *str) {
    char result = 0;
    while (*str) {
        if (*str < '0' || *str > '9') break;  // Not a number
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}


int main() {
    char buffer_size = 100;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    //make sure that memeory was allocated correctly
    if (buffer == NULL){
      printf("Failed to allocate memory\n");
	goto out;
    }

    //initialize history
    List *history = init_history();
    if (history == NULL) {
        printf("Failed to initialize history.\n");
        goto out;
    }
    
 top:
        printf("$ ");
        
        //read input using fgets
        if (fgets(buffer, buffer_size, stdin) != NULL) {
	 //check if input is longer than the buffer size
         char i = 0;
         char is_full = 1;
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

	  // check if 'history'
	  if(buffer[0] == 'h' && buffer[1] == 'i' && buffer[2] == 's' && buffer[3] == 't' && buffer[4] == 'o' &&buffer[5] == 'r' && buffer[6] == 'y' && buffer[7] == '\0'){
	    print_history(history);
	    goto top;
	  }

	  //check for specific history
          if (buffer[0] == '!' && buffer[1] != '\0') {
            char history_id = turn_to_int(&buffer[1]);  //turn string into number
            char *history_command = get_history(history, history_id);
            if (history_command != NULL) {
                printf("%s\n", history_command);
		char *end = history_command;
		while(*end != '\0'){
		  end++;
		}
		char str_len = end - history_command;
                buffer = copy_str(history_command, str_len);
            } else {
                printf("No history entry found for ID %d\n", history_id);
                goto top;
            }
          }

	  //add user input to history
	  add_history(history,buffer);
	  

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
    //free the memory allocated by the buffer and history
    free(buffer);
    free_history(history);
    return 0;
}
