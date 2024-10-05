#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

/* Return true (non-zero) if c is a whitespace character ('\t' or ' '). */
int space_char(char c) {
    return (c == ' ' || c == '\t') && c != '\0';
}

/* Return true (non-zero) if c is a non-whitespace character (not tab or space). */
int non_space_char(char c) {
    return c != ' ' && c != '\t' && c != '\0';
}

/* Returns a pointer to the first character of the next space-separated token. */
char *token_start(char *str) {
    if (str == NULL) return NULL;

    //traverses until a nonspace character is found or its the end of the string             
    while (*str != '\0' && space_char(*str)) {
        str++;
    }                                                               
    return *str != '\0' ? str : NULL;
}

/* Returns a pointer to the character following the end of a token. */
char *token_terminator(char *token) {
    if (token == NULL) return NULL;

    //traverses until space or end of string                                         
    while (*token != '\0' && non_space_char(*token)) {
        token++;
    }
    return token; //returns pointer to the char after the token                             
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str) {
    int count = 0;
    char *current = str;

    //find each token and go to the terminator         
    while ((current = token_start(current)) != NULL) {
        count++;
        current = token_terminator(current);         
    }
    return count;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr>. */
char *copy_str(char *inStr, short len) {
    char *copy = (char *)malloc((len + 1) * sizeof(char));
    if (copy == NULL) {
        return NULL;
    }

    for (short i = 0; i < len; i++) {
        copy[i] = inStr[i];
    }
    copy[len] = '\0';
    return copy;
}


char **tokenize(char *str) {
    if (str == NULL) return NULL;

    int num_tokens = count_tokens(str); 
    
    //alloctaes memory for the array + 1 for the null'0' operator
    char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    if (tokens == NULL) {
        return NULL; //memory allocation failed
    }
    
    char *current = str;
    int index = 0;

    //extarct tokens and store pointers
    while ((current = token_start(current)) != NULL) { //start of token
        char *end = token_terminator(current); //end of token
        int token_len = end - current;

        //finds the tokens and stores them in the array
        tokens[index] = copy_str(current, token_len);
        if (tokens[index] == NULL) {
	  //if allocation fails then free tokens one by one
            for (int j = 0; j < index; j++) {
                free(tokens[j]);
            }
            free(tokens);
            return NULL;
        }
        index++;
        current = end; //move to the next token
    }
    tokens[index] = NULL; //assigns null '0' to the last element in the array

    return tokens;
}

//prints tokens
void print_tokens(char **tokens) {
    if (tokens == NULL) return;

    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token[%d]: %s\n", i, tokens[i]);
    }
}

// frees memory
void free_tokens(char **tokens) {
    if (tokens == NULL) return;

    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]); 
    }
    free(tokens); 
}
