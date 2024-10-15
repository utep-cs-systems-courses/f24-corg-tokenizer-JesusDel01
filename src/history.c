#include "history.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

// initialize the linked list to keep history
List* init_history() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL; 
    }
    list->root = NULL; // the list is empty when we start
    return list;
}

//add a history item to the end of list
void add_history(List *list, char *str) {
    if (list == NULL || str == NULL) return;

    Item *new_item = (Item *)malloc(sizeof(Item));
    if (new_item == NULL) {
        return; 
    }

    // calculate the length of the string
    char *end = str;
    while(*end != '\0'){
      end++;
    }

    char str_len = end - str; 

    //allocate memory for the string and copy it using the copy_str function from tokenozer.c
    new_item->str = copy_str(str, str_len);
    if (new_item->str == NULL){
      free(new_item);
      return;
    }
    

    //find the last item and  append the new item
    if (list->root == NULL) {
        new_item->id = 1;
        new_item->next = NULL;
        list->root = new_item;
    } else {
        Item *current = list->root;
        while (current->next != NULL) {
            current = current->next;
        }
        new_item->id = current->id + 1; //increment ID
        new_item->next = NULL;          //end of the list
        current->next = new_item;       //attach to the last item
    }
}

//retrieve the string stored in the node where Item->id == id
char *get_history(List *list, int id) {
    if (list == NULL) return NULL;

    Item *current = list->root;
    while (current != NULL) {
        if (current->id == id) {
	  return current->str; //finds the item
        }
        current = current->next; //goes to the next item
    }
    return NULL; 
}

//prints the entire history
void print_history(List *list) {
    if (list == NULL) return;

    Item *current = list->root;
    while (current != NULL) {
        printf("%d: %s\n", current->id, current->str);
        current = current->next;
    }
}

//free the history
void free_history(List *list) {
    if (list == NULL) return;

    Item *current = list->root;
    while (current != NULL) {
        Item *next = current->next;
        free(current->str);  //free the stored string
        free(current);       //free the current item
        current = next;      //go to the next item
    }

    free(list); //free the actual list
}
