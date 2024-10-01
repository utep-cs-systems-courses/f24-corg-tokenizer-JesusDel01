#include <stdio.h>
#include <stdlib.h>
int main() {
  char *input = NULL;
  size_t len = 0;

  printf("$ ");

  getline(&input, &len, stdin);

  free(input);    
  return 0;
}
