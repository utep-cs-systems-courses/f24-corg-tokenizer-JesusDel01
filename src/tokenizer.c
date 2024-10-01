#include "tokenizer.h"
#include <stdlib.h> 

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
