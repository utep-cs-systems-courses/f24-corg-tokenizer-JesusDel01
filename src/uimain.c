#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

int main() {
    char buffer[100];

    while (1) {
        printf("$ ");
        
        //read input using fgets
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
	  buffer[strcspn(buffer, "\n")] = '\0'; // gets rid of the newline character

            //check if "exit"
            if (strcmp(buffer, "exit") == 0) {
                break; //breaks the program
            }

	    char **tokens = tokenize(buffer);
	    if(tokens != NULL){
	      print_tokens(tokens);
	      free_tokens(tokens);
		
	    }

        } else {
            printf("Error reading input.\n");
            break;
        }
    }

    return 0;
}
